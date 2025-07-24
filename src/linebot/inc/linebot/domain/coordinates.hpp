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

    const etl::array<uint8_t, MAX_LENGTH> values_;
    const etl::array<int8_t, MAX_LENGTH>  weights_;
    const uint8_t                         length_;

    static coordinates
    of_6(
        uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3
    );

    static coordinates
    of_6(etl::array<uint8_t, MAX_LENGTH> values);

    template <typename T>
    etl::optional<int8_t>
    compute_error(coordinates_error_strategy<T>& strategy) const
    {
        return strategy.compute(*this);
    }

    bool
    is_on_finish() const;

    bool
    is_on_route() const;

    bool
    operator==(const coordinates& other) const;
};

} // namespace linebot
