#pragma once

#include "driver/rmt_encoder.h"
#include "driver/rmt_tx.h"
#include "driver/rmt_types.h"
#include "esp_err.h"
#include "hal/gpio_types.h"
#include "hal/rmt_types.h"
#include "soc/gpio_num.h"
#include <cstdint>
#include "../Utils/FixedSizeQueue.hpp"

template <size_t queueCapacity>
class IRTransmitter {
public:
    explicit IRTransmitter(gpio_num_t txPin = GPIO_NUM_30) {
        TX_PIN = txPin;

        txChannelCfg = {
            .gpio_num = TX_PIN,
            .clk_src = RMT_CLK_SRC_DEFAULT,
            .resolution_hz = IR_RESOLUTION_HZ,
            .mem_block_symbols = 1024,
            .trans_queue_depth = queueCapacity,
            .intr_priority = 1,
            .flags = {.invert_out = false,
            .with_dma = true,
            .allow_pd = false, },
        };

        ESP_ERROR_CHECK(rmt_new_tx_channel(&txChannelCfg, &txChannel));

        txCarrierCfg = {
            .frequency_hz = 37800,
            .duty_cycle = 0.50f,
            .flags = {.polarity_active_low = false,
            .always_on = false, },
        };

        ESP_ERROR_CHECK(rmt_apply_carrier(txChannel, &txCarrierCfg));

        txConfig = {
            .loop_count = 0,
            .flags = { .eot_level = false,
            .queue_nonblocking = true, },
        };

        configureEncoder();

        ESP_ERROR_CHECK(rmt_enable(txChannel));
    }

    ~IRTransmitter() {
        ESP_ERROR_CHECK(rmt_del_encoder(vovoIREncoder->copyEncoder));
        ESP_ERROR_CHECK(rmt_del_encoder(vovoIREncoder->bytesEncoder));
        delete vovoIREncoder;

        ESP_ERROR_CHECK(rmt_del_channel(txChannel));
    }

    esp_err_t transmitCode(uint32_t code) {
        VovoCode vovoCode = {.code = reverseBits(code)};
        
        return rmt_transmit(txChannel, txEncoderHandle, codeQueue.enqueue(vovoCode), sizeof(VovoCode), &txConfig);
    }

    gpio_num_t getTXPin() {
        return TX_PIN;
    }

private:
    struct VovoCode {
        uint32_t code;
    };

    struct VovoIREncoder {
      rmt_encoder_t base;
      rmt_encoder_t *copyEncoder;
      rmt_encoder_t *bytesEncoder;
      rmt_symbol_word_t vovoLeadingSymbol;
      rmt_symbol_word_t vovoEndingSymbol;
      int state;
    };

    void configureEncoder() {
        leadingSymbol = {
            .duration0 = 3975ULL * US_TO_TICKS,
            .level0 = 1,
            .duration1 = 8000ULL * US_TO_TICKS,
            .level1 = 0,
        };

        endingSymbol = {
            .duration0 = 490ULL * US_TO_TICKS,
            .level0 = 1,
            .duration1 = 3975ULL * US_TO_TICKS,
            .level1 = 0,
        };

        bytesEncoderConfig = {
            .bit0 = {
                .duration0 = 490ULL * US_TO_TICKS,
                .level0 = 1,
                .duration1 = 515ULL * US_TO_TICKS,
                .level1 = 0,
            },
            .bit1 = {
                .duration0 = 490ULL * US_TO_TICKS,
                .level0 = 1,
                .duration1 = 1496ULL * US_TO_TICKS,
                .level1 = 0,
            },
            .flags = {.msb_first = 0,},
        };

        vovoIREncoder = new VovoIREncoder();
        vovoIREncoder->state = 0;
        vovoIREncoder->base.encode = vovoEncodeIR;
        vovoIREncoder->base.del = vovoDeleteEncoder;
        vovoIREncoder->base.reset = vovoResetEncoder;

        rmt_copy_encoder_config_t copyEncoderCfg = {};
        rmt_new_copy_encoder(&copyEncoderCfg, &vovoIREncoder->copyEncoder);

        vovoIREncoder->vovoLeadingSymbol = leadingSymbol;
        vovoIREncoder->vovoEndingSymbol = endingSymbol;

        rmt_new_bytes_encoder(&bytesEncoderConfig, &vovoIREncoder->bytesEncoder);

        txEncoderHandle = &vovoIREncoder->base;
    }

    static esp_err_t vovoDeleteEncoder(rmt_encoder_t *encoder) {
        VovoIREncoder *vovoEncoder = reinterpret_cast<VovoIREncoder*>(encoder);
        rmt_del_encoder(vovoEncoder->copyEncoder);
        rmt_del_encoder(vovoEncoder->bytesEncoder);
        delete vovoEncoder;
        return ESP_OK;
    }

    static esp_err_t vovoResetEncoder(rmt_encoder_t *encoder) {
        VovoIREncoder *vovoEncoder = reinterpret_cast<VovoIREncoder*>(encoder);
        rmt_encoder_reset(vovoEncoder->copyEncoder);
        rmt_encoder_reset(vovoEncoder->bytesEncoder);
        vovoEncoder->state = 0;
        return ESP_OK;
    }

    static size_t vovoEncodeIR(rmt_encoder_t *encoder, rmt_channel_handle_t channel, const void *primaryData, size_t dataSize, rmt_encode_state_t *returnState) {
        VovoIREncoder *vovoEncoder = reinterpret_cast<VovoIREncoder*>(encoder);
        rmt_encode_state_t sessionState = RMT_ENCODING_RESET;
        rmt_encode_state_t state = RMT_ENCODING_RESET;
        size_t encodedSymbols = 0;

        VovoCode* code = (VovoCode*) primaryData;
        rmt_encoder_handle_t copyEncoder = vovoEncoder->copyEncoder;
        rmt_encoder_handle_t bytesEncoder = vovoEncoder->bytesEncoder;

        switch (vovoEncoder->state) {
        case 0: // Leading Code
            encodedSymbols += copyEncoder->encode(copyEncoder, channel, &vovoEncoder->vovoLeadingSymbol, sizeof(rmt_symbol_word_t), &sessionState);

            if (sessionState & RMT_ENCODING_COMPLETE) {
                vovoEncoder->state++;
            }
            if (sessionState & RMT_ENCODING_MEM_FULL) {
                state = static_cast<rmt_encode_state_t>(state | RMT_ENCODING_MEM_FULL);
                break;
            }
        // Fall-through
        case 1: // Data Code
            encodedSymbols += bytesEncoder->encode(bytesEncoder, channel, &code->code, sizeof(uint32_t), &sessionState);

            if (sessionState & RMT_ENCODING_COMPLETE) {
                vovoEncoder->state++;
            }
            if (sessionState & RMT_ENCODING_MEM_FULL) {
                state = static_cast<rmt_encode_state_t>(state | RMT_ENCODING_MEM_FULL);
                break;
            }
        // Fall-through
        case 2: // Ending Code
            encodedSymbols += copyEncoder->encode(copyEncoder, channel, &vovoEncoder->vovoEndingSymbol, sizeof(rmt_symbol_word_t), &sessionState);

            if (sessionState & RMT_ENCODING_COMPLETE) {
                vovoEncoder->state = RMT_ENCODING_RESET; // back to the initial encoding session
                state = static_cast<rmt_encode_state_t>(state | RMT_ENCODING_COMPLETE);
            }
            if (sessionState & RMT_ENCODING_MEM_FULL) {
                state = static_cast<rmt_encode_state_t>(state | RMT_ENCODING_MEM_FULL);
                break;
            }
        }

        *returnState = state;
        return encodedSymbols;
    }

    static uint32_t reverseBits(uint32_t n) {
        n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
        n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
        n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
        n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
        n = (n >> 16) | (n << 16);
        return n;
    }

    rmt_channel_handle_t txChannel;
    rmt_tx_channel_config_t txChannelCfg;
    rmt_carrier_config_t txCarrierCfg;
    rmt_transmit_config_t txConfig;

    // RMT Encoder
    VovoIREncoder *vovoIREncoder;
    rmt_encoder_handle_t txEncoderHandle;
    rmt_bytes_encoder_config_t bytesEncoderConfig;
    rmt_symbol_word_t leadingSymbol;
    rmt_symbol_word_t endingSymbol;
    
    FixedSizeQueue<VovoCode, queueCapacity> codeQueue;

    static constexpr uint32_t IR_RESOLUTION_HZ = 1000000;
    static constexpr uint16_t US_TO_TICKS = IR_RESOLUTION_HZ / 1000000;
    gpio_num_t TX_PIN;
};
