#pragma once

#include <cstdint>
#include <etl/array.h>

namespace linebot
{

struct coordinates
{
    constexpr static uint8_t max_length = 6;

    const etl::array<uint8_t, max_length> values;
    const etl::array<int8_t, max_length>  weights;
    const uint8_t                         length;

    bool
    operator==(const coordinates&) const = default;
};

} // namespace linebot
