#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/mode.hpp"
#include <tuple>

namespace linebot
{

static const coordinates COORD_ON_ROUTE  = coordinates::of_6(80, 0, 0, 0, 0, 0);
static const coordinates COORD_ON_FINISH = coordinates::of_6(5, 0, 0, 0, 0, 5);
static const coordinates COORD_OFF_ROUTE = coordinates::of_6(0, 0, 0, 0, 0, 0);

TEST_CASE_METHOD(
    api_fixture, "should switch mode by line position", "[linebot]"
)
{
    using params_type = std::tuple<mode, coordinates, mode>;

    auto params = GENERATE(
        params_type{mode::MANUAL, COORD_ON_ROUTE, mode::LINE_DETECTED},
        params_type{mode::LINE_DETECTED, COORD_OFF_ROUTE, mode::MANUAL},
        params_type{mode::FOLLOWING, COORD_ON_FINISH, mode::MANUAL},
        params_type{mode::RECOVERING, COORD_ON_FINISH, mode::MANUAL},
        params_type{mode::FOLLOWING, COORD_OFF_ROUTE, mode::RECOVERING},
        params_type{mode::RECOVERING, COORD_ON_ROUTE, mode::FOLLOWING}
    );

    // given
    auto current_mode  = std::get<0>(params);
    auto line_position = std::get<1>(params);
    auto expected_mode = std::get<2>(params);

    CAPTURE(current_mode, line_position, expected_mode);

    store_.mode_          = current_mode;
    store_.line_position_ = line_position;

    // when
    api_.switch_mode_by_line_position();

    // then
    REQUIRE(status_indicator_.applied_mode_.has_value());
    CHECK(status_indicator_.applied_mode_.value() == expected_mode);
    CHECK(store_.mode_ == expected_mode);
}

TEST_CASE_METHOD(
    api_fixture, "should not switch to detected when tracking", "[linebot][bug]"
)
{
    // given
    store_.mode_          = mode::FOLLOWING;
    store_.line_position_ = coordinates::of_6(20, 20, 20, 20, 20, 20);

    // when
    api_.switch_mode_by_line_position();

    // then
    CHECK(store_.mode_ == mode::FOLLOWING);
    CHECK(mode::FOLLOWING == 2);
}

} // namespace linebot
