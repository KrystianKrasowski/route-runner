#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include <cstdint>
#include <etl/array.h>
#include <etl/circular_buffer.h>
#include <tuple>

namespace linebot
{

TEST_CASE_METHOD(
    api_fixture,
    "should maneuver by line position in tracking mode",
    "[linebot]"
)
{
    SECTION("turning left")
    {
        // given
        coordinates line_position = GENERATE(
            coordinates::of_6(0, 20, 100, 80, 0, 0),
            coordinates::of_6(0, 40, 100, 60, 0, 0),
            coordinates::of_6(0, 60, 100, 40, 0, 0),
            coordinates::of_6(0, 80, 100, 20, 0, 0),
            coordinates::of_6(0, 100, 100, 0, 0, 0),
            coordinates::of_6(20, 100, 80, 0, 0, 0),
            coordinates::of_6(40, 100, 60, 0, 0, 0),
            coordinates::of_6(60, 100, 40, 0, 0, 0),
            coordinates::of_6(80, 100, 20, 0, 0, 0),
            coordinates::of_6(100, 100, 0, 0, 0, 0),
            coordinates::of_6(100, 80, 0, 0, 0, 0),
            coordinates::of_6(100, 60, 0, 0, 0, 0),
            coordinates::of_6(100, 40, 0, 0, 0, 0),
            coordinates::of_6(100, 20, 0, 0, 0, 0),
            coordinates::of_6(100, 0, 0, 0, 0, 0)
        );

        store_.mode_          = GENERATE(mode::FOLLOWING, mode::RECOVERING);
        store_.line_position_ = line_position;

        // when
        api_.apply_motion_by_line_position();

        // then
        REQUIRE(motion_.applied_maneuver_.has_value());

        maneuver& actual_maneuver = motion_.applied_maneuver_.value();

        CHECK(actual_maneuver.get_direction() == maneuver::FORWARD);
        CHECK((int)actual_maneuver.get_correction() < 0);
    }

    SECTION("turn right")
    {
        // given
        coordinates line_position = GENERATE(
            coordinates::of_6(0, 0, 80, 100, 20, 0),
            coordinates::of_6(0, 0, 60, 100, 40, 0),
            coordinates::of_6(0, 0, 40, 100, 60, 0),
            coordinates::of_6(0, 0, 20, 100, 80, 0),
            coordinates::of_6(0, 0, 0, 100, 100, 0),
            coordinates::of_6(0, 0, 0, 80, 100, 20),
            coordinates::of_6(0, 0, 0, 60, 100, 40),
            coordinates::of_6(0, 0, 0, 40, 100, 60),
            coordinates::of_6(0, 0, 0, 20, 100, 80),
            coordinates::of_6(0, 0, 0, 0, 100, 100),
            coordinates::of_6(0, 0, 0, 0, 80, 100),
            coordinates::of_6(0, 0, 0, 0, 60, 100),
            coordinates::of_6(0, 0, 0, 0, 40, 100),
            coordinates::of_6(0, 0, 0, 0, 20, 100),
            coordinates::of_6(0, 0, 0, 0, 0, 100)
        );

        store_.mode_          = GENERATE(mode::FOLLOWING, mode::RECOVERING);
        store_.line_position_ = line_position;

        // when
        api_.apply_motion_by_line_position();

        // then
        REQUIRE(motion_.applied_maneuver_.has_value());

        maneuver& actual_maneuver = motion_.applied_maneuver_.value();

        CHECK(actual_maneuver.get_direction() == maneuver::FORWARD);
        CHECK((int)actual_maneuver.get_correction() > 0);
    }

    SECTION("stop on finish")
    {
        // given
        store_.mode_          = mode::FOLLOWING;
        store_.line_position_ = coordinates::of_6(5, 0, 0, 0, 0, 5);

        // when
        api_.apply_motion_by_line_position();

        // then
        REQUIRE(motion_.applied_maneuver_.has_value());

        maneuver& actual_maneuver = motion_.applied_maneuver_.value();

        CHECK(actual_maneuver.get_direction() == maneuver::NONE);
        CHECK((int)actual_maneuver.get_correction() == 0);
    }

    SECTION("compute and store position error")
    {
        using params_type = std::tuple<coordinates, int8_t>;

        auto params = GENERATE(
            params_type{coordinates::of_6(100, 0, 0, 0, 0, 0), -100},
            params_type{coordinates::of_6(100, 10, 0, 0, 0, 0), -94},
            params_type{coordinates::of_6(100, 20, 0, 0, 0, 0), -90},
            params_type{coordinates::of_6(100, 30, 0, 0, 0, 0), -86},
            params_type{coordinates::of_6(100, 40, 0, 0, 0, 0), -82},
            params_type{coordinates::of_6(100, 50, 0, 0, 0, 0), -80},
            params_type{coordinates::of_6(100, 60, 0, 0, 0, 0), -77},
            params_type{coordinates::of_6(100, 70, 0, 0, 0, 0), -75},
            params_type{coordinates::of_6(100, 80, 0, 0, 0, 0), -73},
            params_type{coordinates::of_6(100, 90, 0, 0, 0, 0), -71},
            params_type{coordinates::of_6(100, 100, 0, 0, 0, 0), -70},
            params_type{coordinates::of_6(90, 100, 10, 0, 0, 0), -66},
            params_type{coordinates::of_6(80, 100, 20, 0, 0, 0), -62},
            params_type{coordinates::of_6(70, 100, 30, 0, 0, 0), -58},
            params_type{coordinates::of_6(60, 100, 40, 0, 0, 0), -54},
            params_type{coordinates::of_6(50, 100, 50, 0, 0, 0), -50},
            params_type{coordinates::of_6(40, 100, 60, 0, 0, 0), -46},
            params_type{coordinates::of_6(30, 100, 70, 0, 0, 0), -42},
            params_type{coordinates::of_6(20, 100, 80, 0, 0, 0), -38},
            params_type{coordinates::of_6(10, 100, 90, 0, 0, 0), -34},
            params_type{coordinates::of_6(0, 100, 100, 0, 0, 0), -30},
            params_type{coordinates::of_6(0, 90, 100, 10, 0, 0), -27},
            params_type{coordinates::of_6(0, 80, 100, 20, 0, 0), -24},
            params_type{coordinates::of_6(0, 70, 100, 30, 0, 0), -21},
            params_type{coordinates::of_6(0, 60, 100, 40, 0, 0), -18},
            params_type{coordinates::of_6(0, 50, 100, 50, 0, 0), -15},
            params_type{coordinates::of_6(0, 40, 100, 60, 0, 0), -12},
            params_type{coordinates::of_6(0, 30, 100, 70, 0, 0), -9},
            params_type{coordinates::of_6(0, 20, 100, 80, 0, 0), -6},
            params_type{coordinates::of_6(0, 10, 100, 90, 0, 0), -3},
            params_type{coordinates::of_6(0, 0, 100, 100, 0, 0), 0},
            params_type{coordinates::of_6(0, 0, 90, 100, 10, 0), 3},
            params_type{coordinates::of_6(0, 0, 80, 100, 20, 0), 6},
            params_type{coordinates::of_6(0, 0, 70, 100, 30, 0), 9},
            params_type{coordinates::of_6(0, 0, 60, 100, 40, 0), 12},
            params_type{coordinates::of_6(0, 0, 50, 100, 50, 0), 15},
            params_type{coordinates::of_6(0, 0, 40, 100, 60, 0), 18},
            params_type{coordinates::of_6(0, 0, 30, 100, 70, 0), 21},
            params_type{coordinates::of_6(0, 0, 20, 100, 80, 0), 24},
            params_type{coordinates::of_6(0, 0, 10, 100, 90, 0), 27},
            params_type{coordinates::of_6(0, 0, 0, 100, 100, 0), 30},
            params_type{coordinates::of_6(0, 0, 0, 90, 100, 10), 34},
            params_type{coordinates::of_6(0, 0, 0, 80, 100, 20), 38},
            params_type{coordinates::of_6(0, 0, 0, 70, 100, 30), 42},
            params_type{coordinates::of_6(0, 0, 0, 60, 100, 40), 46},
            params_type{coordinates::of_6(0, 0, 0, 50, 100, 50), 50},
            params_type{coordinates::of_6(0, 0, 0, 40, 100, 60), 54},
            params_type{coordinates::of_6(0, 0, 0, 30, 100, 70), 58},
            params_type{coordinates::of_6(0, 0, 0, 20, 100, 80), 62},
            params_type{coordinates::of_6(0, 0, 0, 10, 100, 90), 66},
            params_type{coordinates::of_6(0, 0, 0, 0, 100, 100), 70},
            params_type{coordinates::of_6(0, 0, 0, 0, 90, 100), 71},
            params_type{coordinates::of_6(0, 0, 0, 0, 80, 100), 73},
            params_type{coordinates::of_6(0, 0, 0, 0, 70, 100), 75},
            params_type{coordinates::of_6(0, 0, 0, 0, 60, 100), 77},
            params_type{coordinates::of_6(0, 0, 0, 0, 50, 100), 80},
            params_type{coordinates::of_6(0, 0, 0, 0, 40, 100), 82},
            params_type{coordinates::of_6(0, 0, 0, 0, 30, 100), 86},
            params_type{coordinates::of_6(0, 0, 0, 0, 20, 100), 90},
            params_type{coordinates::of_6(0, 0, 0, 0, 10, 100), 94},
            params_type{coordinates::of_6(0, 0, 0, 0, 0, 100), 100}
        );

        // given
        store_.mode_          = mode::FOLLOWING;
        store_.line_position_ = std::get<0>(params);
        int expected_error    = std::get<1>(params);

        // when
        api_.apply_motion_by_line_position();
        int actual_error = store_.errors_.back();

        // then
        CHECK(actual_error == expected_error);
    }
}

} // namespace linebot
