#include "catch2/catch_test_macros.hpp"
#include "mapper/qtrhd06a_coordinates.hpp"
#include <cstdint>
#include <etl/array.h>

namespace mapper
{

TEST_CASE("should normalize line sensor values", "[mapper]")
{
    // given
    etl::array<uint8_t, 6> raw_values{20, 18, 110, 105, 15, 21};
    etl::array<uint8_t, 6> expected_coordinates{0, 0, 90, 85, 0, 1};

    // when
    auto actual_coordinates = map(raw_values);

    // then
    CHECK(actual_coordinates == expected_coordinates);
}

} // namespace mapper
