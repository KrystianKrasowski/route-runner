#pragma once

#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/coordinates_error_strategy.hpp"
#include <cstdint>
#include <etl/optional.h>

namespace linebot
{

struct coordinates_error_center_of_mass
    : public coordinates_error_strategy<coordinates_error_center_of_mass>
{
    etl::optional<int8_t>
    // cppcheck-suppress unusedFunction
    do_compute(const coordinates& line_position)
    {
        etl::optional<int8_t> result;

        int16_t sum        = 0;
        int16_t weight_sum = 0;
        auto    length     = line_position.get_length();
        auto    values     = line_position.get_values();
        auto    weights    = line_position.get_weights();

        for (uint8_t i = 0; i < length; i++)
        {
            auto value  = values[i];
            auto weight = weights[i];

            sum        += value;
            weight_sum += (value * weight);
        }

        if (sum != 0)
        {
            int8_t center = weight_sum / sum;
            result        = etl::optional<int8_t>{center};
        }

        return result;
    }
};

} // namespace linebot
