#pragma once

#include <cstdint>
#include <etl/array.h>

namespace linebot
{

struct coordinates
{
    constexpr static uint8_t max_length = 6;

    const etl::array<uint8_t, max_length> values_;
    const etl::array<int8_t, max_length>  weights_;
    const uint8_t                         length_;

    bool
    operator==(const coordinates& other) const
    {
        return values_ == other.values_ && weights_ == other.weights_
            && length_ == other.length_;
    }
};

} // namespace linebot
