#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/remote_control.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace linebot
{

constexpr auto FORWARD  = remote_control::FORWARD;
constexpr auto LEFT     = remote_control::LEFT;
constexpr auto RIGHT    = remote_control::RIGHT;
constexpr auto BACKWARD = remote_control::BACKWARD;

TEST_CASE_METHOD(
    api_fixture,
    "should maneuver by remote control in non-tracking mode",
    "[linebot]"
)
{
    using example_type = std::tuple<remote_control, maneuver>;

    auto mode    = GENERATE(mode::MANUAL, mode::LINE_DETECTED);
    auto example = GENERATE(
        example_type{remote_control{FORWARD}, maneuver::forward(0)},
        example_type{remote_control{FORWARD | LEFT}, maneuver::forward(-50)},
        example_type{remote_control{FORWARD | RIGHT}, maneuver::forward(50)},
        example_type{remote_control{BACKWARD}, maneuver::backward(0)},
        example_type{remote_control{BACKWARD | LEFT}, maneuver::backward(-50)},
        example_type{remote_control{BACKWARD | RIGHT}, maneuver::backward(50)},
        example_type{remote_control{LEFT}, maneuver::none()},
        example_type{remote_control{RIGHT}, maneuver::none()},
        example_type{remote_control{LEFT | RIGHT}, maneuver::none()}
    );

    auto new_remote_control = std::get<0>(example);
    auto expected_maneuver  = std::get<1>(example);

    CAPTURE(mode, new_remote_control, expected_maneuver);

    // given
    store_.remote_control_ = new_remote_control;
    store_.mode_           = mode;

    // when
    api_.apply_motion_by_remote();

    // then
    REQUIRE(motion_.applied_maneuver_.has_value());
    REQUIRE(motion_.applied_maneuver_.value() == expected_maneuver);
}

} // namespace linebot
