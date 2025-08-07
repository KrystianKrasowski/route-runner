#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/actions.hpp"
#include "linebot/domain/coordinates.hpp"

namespace linebot
{

static const auto COORDS_OFF_ROUTE = coordinates::of_6(0, 0, 0, 0, 0, 0);
static const auto COORDS_ON_ROUTE  = coordinates::of_6(0, 0, 100, 100, 0, 0);
static const auto COORDS_ON_FINISH = coordinates::of_6(5, 0, 0, 0, 0, 5);

using actions::APPLY_MANEUVER_BY_COORDS;
using actions::CHANGE_MODE_BY_COORDS;
using actions::NONE;
using actions::ROUTE_GUARD_TOGGLE;

TEST_CASE_METHOD(
    api_fixture,
    "should dispatch actions for line position",
    "[linebot][diaptch]"
)
{
    using param_type = std::tuple<mode, coordinates, uint8_t>;

    auto params = GENERATE(
        param_type{mode::MANUAL, COORDS_OFF_ROUTE, NONE},
        param_type{mode::MANUAL, COORDS_ON_ROUTE, CHANGE_MODE_BY_COORDS},
        param_type{mode::FOLLOWING, COORDS_ON_ROUTE, APPLY_MANEUVER_BY_COORDS},
        param_type{
            mode::FOLLOWING,
            COORDS_OFF_ROUTE,
            APPLY_MANEUVER_BY_COORDS | ROUTE_GUARD_TOGGLE
        },
        param_type{
            mode::RECOVERING, COORDS_OFF_ROUTE, APPLY_MANEUVER_BY_COORDS
        },
        param_type{
            mode::RECOVERING,
            COORDS_ON_ROUTE,
            APPLY_MANEUVER_BY_COORDS | ROUTE_GUARD_TOGGLE
        },
        param_type{
            mode::FOLLOWING,
            COORDS_ON_FINISH,
            APPLY_MANEUVER_BY_COORDS | CHANGE_MODE_BY_COORDS
        }
    );

    auto mode             = std::get<0>(params);
    auto line_position    = std::get<1>(params);
    auto expected_actions = std::get<2>(params);

    // given
    store_.mode_ = mode;

    // when
    auto actions = api_.query(line_position);

    // then
    CHECK(actions.contain(expected_actions));
    CHECK(store_.line_position_ == line_position);
}

} // namespace linebot
