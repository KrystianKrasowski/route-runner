#pragma once

#include "linebot/domain/coordinates_error_strategy.hpp"
#include <cstdint>
#include <etl/array.h>
#include <etl/optional.h>

namespace linebot
{

struct coordinates
{
    constexpr static uint8_t max_length = 6;

    const etl::array<uint8_t, max_length> values_;
    const etl::array<int8_t, max_length>  weights_;
    const uint8_t                         length_;

    static coordinates
    of_6(
        uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3
    );

    template <typename T>
    etl::optional<int8_t>
    compute_error(coordinates_error_strategy<T>& strategy)
    {
        return strategy.compute(*this);
    }

    bool
    is_on_finish();

    bool
    is_on_route();

    bool
    operator==(const coordinates& other) const;
};

} // namespace linebot
