#pragma once

#include "stdint.h"

class RemoteSettings
{
public:
    enum class Temperature : uint8_t
    {
        Low = 0,
        MediumLow = 1,
        MediumHigh = 2,
        High = 3
    };

    enum class WashMode : int8_t
    {
        Stopped = -1,
        PosteriorContinuous = 0,
        PosteriorRhythm = 1,
        PosteriorTurbo = 2,
        FeminineContinuous = 3,
        FeminineRhythm = 4,
        Drying = 5
    };

    enum class PressureMode : uint8_t
    {
        Lowest = 0,
        Low = 1,
        Medium = 2,
        High = 3,
        Highest = 4
    };

    enum class PositionMode : uint8_t
    {
        UpFront = 0,
        Front = 1,
        Middle = 2,
        Back = 3,
        FarBack = 4
    };
};