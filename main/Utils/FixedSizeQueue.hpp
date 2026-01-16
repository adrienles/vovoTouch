#pragma once

#include <stdint.h>
#include <array>

template <typename T, uint8_t capacity>
class FixedSizeQueue
{
public:
    FixedSizeQueue() = default;
    ~FixedSizeQueue() = default;

    T* enqueue(const T &item)
    {
        // if (size == capacity)
        // {
        //     return;
        // }

        uint8_t backIndex = (frontIndex + size) % capacity;
        data[backIndex] = item;
        size++;

        return &data[backIndex];
    }

    const T &deque()
    {
        if (empty())
        {
            return nullptr;
        }

        T &dequeuedItem = data[frontIndex];

        frontIndex = (frontIndex + 1) % capacity;
        size--;

        return dequeuedItem;
    }

    const T &peek()
    {
        if (empty())
        {
            return nullptr;
        }

        return data[frontIndex];
    }

    bool empty() const
    {
        return size == 0;
    }

    uint8_t getSize() const
    {
        return size;
    }

    uint8_t getCapacity() const
    {
        return capacity;
    }

private:
    std::array<T, capacity> data;
    uint8_t frontIndex = 0;
    uint8_t size = 0;
};
