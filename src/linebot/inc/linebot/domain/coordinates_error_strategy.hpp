#pragma once

#include <cstdint>
#include <etl/optional.h>

namespace linebot
{

struct coordinates;

template <typename T>
struct coordinates_error_strategy
{
    etl::optional<int8_t>
    compute(const coordinates& line_position)
    {
        auto* strategy = static_cast<T*>(this);
        return strategy->do_compute(line_position);
    }
};

} // namespace linebot
