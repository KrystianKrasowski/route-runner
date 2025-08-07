#pragma once

#include "linebot/domain/coordinates_error_strategy.hpp"
#include <cstdint>
#include <etl/array.h>
#include <etl/optional.h>

namespace linebot
{

struct coordinates
{
    constexpr static uint8_t MAX_LENGTH = 6;

    static coordinates
    of_6(uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3)
    {
        etl::array<uint8_t, MAX_LENGTH> values{l3, l2, l1, r1, r2, r3};
        return {values, WEIGHTS_6, MAX_LENGTH};
    }

    static coordinates
    of_6(etl::array<uint8_t, MAX_LENGTH> values)
    {
        return {values, WEIGHTS_6, MAX_LENGTH};
    }

    template <typename T>
    etl::optional<int8_t>
    compute_error(coordinates_error_strategy<T>& strategy) const
    {
        return strategy.compute(*this);
    }

    bool
    is_on_finish() const
    {
        uint8_t last_index = length_ - 1;
        uint8_t mid_index  = length_ / 2;

        bool first_on_route = values_[0] >= DETECTION_TRESHOLD;
        bool last_on_route  = values_[last_index] >= DETECTION_TRESHOLD;
        bool mid_off_route  = false;

        if ((length_ & 1) == 0)
        {
            mid_off_route = values_[mid_index] < DETECTION_TRESHOLD
                         && values_[mid_index - 1] < DETECTION_TRESHOLD;
        }
        else
        {
            mid_off_route = values_[mid_index + 1] < DETECTION_TRESHOLD
                         && values_[mid_index] < DETECTION_TRESHOLD
                         && values_[mid_index - 1] < DETECTION_TRESHOLD;
        }

        return first_on_route && mid_off_route && last_on_route;
    }

    bool
    is_on_route() const
    {
        return etl::any_of(values_.begin(), values_.end(), is_detected);
    }

    etl::array<uint8_t, MAX_LENGTH>
    get_values() const
    {
        return values_;
    }

    etl::array<int8_t, MAX_LENGTH>
    get_weights() const
    {
        return weights_;
    }

    uint8_t
    get_length() const
    {
        return length_;
    }

    bool
    operator==(const coordinates& other) const
    {
        return values_ == other.values_ && weights_ == other.weights_
            && length_ == other.length_;
    }

private:

    static constexpr uint8_t                        DETECTION_TRESHOLD = 3;
    static constexpr etl::array<int8_t, MAX_LENGTH> WEIGHTS_6          = {
        -100, -40, -20, 20, 40, 100
    };

    etl::array<uint8_t, MAX_LENGTH> values_;
    etl::array<int8_t, MAX_LENGTH>  weights_;
    uint8_t                         length_;

    coordinates(
        etl::array<uint8_t, MAX_LENGTH> values,
        etl::array<int8_t, MAX_LENGTH>  weights,
        uint8_t                         length
    )
        : values_{values},
          weights_{weights},
          length_{length}
    {
    }

    static bool
    is_detected(uint8_t value)
    {
        return value >= DETECTION_TRESHOLD;
    }
};

} // namespace linebot
