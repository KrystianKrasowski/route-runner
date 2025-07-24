#pragma once

#include "linebot/domain/coordinates.hpp"
#include <cstdint>
#include <etl/array.h>

namespace mapper
{

template <size_t N>
linebot::coordinates
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

    return linebot::coordinates::of_6(result);
}

} // namespace mapper
