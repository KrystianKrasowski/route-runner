#include "catch2/catch_test_macros.hpp"
#include "linebot/domain/coordinates.hpp"
#include "mapper/qtrhd06a_coordinates.hpp"
#include <cstdint>
#include <etl/array.h>

namespace mapper
{

TEST_CASE("should normalize line sensor values", "[mapper]")
{
    // given
    auto raw_values = etl::make_array<uint8_t>(20, 18, 110, 105, 15, 21);
    auto expected_coordinates = linebot::coordinates::of_6(0, 0, 90, 85, 0, 1);

    // when
    auto actual_coordinates = map(raw_values);

    // then
    CHECK(actual_coordinates == expected_coordinates);
}

} // namespace mapper
