#pragma once

#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/coordinates_error_strategy.hpp"
#include <cstdint>
#include <etl/optional.h>

namespace linebot
{

// TODO: Should this be in a header?
struct coordinates_error_center_of_mass
    : public coordinates_error_strategy<coordinates_error_center_of_mass>
{
    etl::optional<int8_t>
    do_compute(coordinates& line_position)
    {
        etl::optional<int8_t> result;

        int16_t sum        = 0;
        int16_t weight_sum = 0;

        for (uint8_t i = 0; i < line_position.length_; i++)
        {
            auto value  = line_position.values_[i];
            auto weight = line_position.weights_[i];

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
