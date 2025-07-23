#pragma once

#include <cstdint>
#include <etl/array.h>

namespace mapper
{

template <size_t N>
etl::array<uint8_t, N>
map(const etl::array<uint8_t, N>& raw_values)
{
    etl::array<uint8_t, N> result;

    for (uint8_t i = 0; i < N; i++)
    {
        uint8_t value = raw_values[i];

        if (value > 120)
        {
            value = 120;
        }

        if (value < 20)
        {
            value = 20;
        }

        result[i] = value - 20;
    }

    return result;
}

} // namespace mapper
