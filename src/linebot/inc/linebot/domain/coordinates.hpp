#pragma once

#include "linebot/domain/coordinates_error_strategy.hpp"
#include <cstdint>
#include <etl/array.h>
#include <etl/optional.h>

namespace linebot
{

class coordinates
{
public:

    constexpr static uint8_t MAX_LENGTH = 6;

    static coordinates
    of_6(
        uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3
    );

    static coordinates
    of_6(etl::array<uint8_t, MAX_LENGTH> values);

    // TODO: Probably remove this. It costs either:
    // * exposing values and weights references via getters, breaks
    // encapsulation and immutability
    // * exposing values and weights via getters, thus copying, causing larger
    // memory footprint (if any, stick with this)
    // * introducing friend class to a template type - mess?
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
    operator==(const coordinates& other) const;

private:

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
};

} // namespace linebot
