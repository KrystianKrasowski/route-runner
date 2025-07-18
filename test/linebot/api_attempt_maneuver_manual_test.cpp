#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace linebot
{

constexpr auto STOP     = commands::STOP;
constexpr auto FORWARD  = commands::FORWARD;
constexpr auto LEFT     = commands::LEFT;
constexpr auto RIGHT    = commands::RIGHT;
constexpr auto BACKWARD = commands::BACKWARD;
constexpr auto BREAK    = commands::BREAK;
constexpr auto FOLLOW   = commands::FOLLOW;

TEST_CASE_METHOD(
    api_fixture,
    "should maneuver by remote control in non-tracking mode",
    "[linebot]"
)
{
    using example_type = std::tuple<commands, maneuver>;

    auto mode    = GENERATE(mode::MANUAL, mode::LINE_DETECTED);
    auto example = GENERATE(
        example_type{commands{FORWARD}, maneuver::forward(0)},
        example_type{commands{FORWARD | LEFT}, maneuver::forward(-50)},
        example_type{commands{FORWARD | RIGHT}, maneuver::forward(50)},
        example_type{commands{BACKWARD}, maneuver::backward(0)},
        example_type{commands{BACKWARD | LEFT}, maneuver::backward(-50)},
        example_type{commands{BACKWARD | RIGHT}, maneuver::backward(50)},
        example_type{commands{LEFT}, maneuver::none()},
        example_type{commands{RIGHT}, maneuver::none()},
        example_type{commands{LEFT | RIGHT}, maneuver::none()}
    );

    auto new_remote_control = std::get<0>(example);
    auto expected_maneuver  = std::get<1>(example);

    CAPTURE(mode, new_remote_control, expected_maneuver);

    // given
    store_.remote_control_ = commands{STOP};
    store_.mode_           = mode;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(motion_port_.applied_maneuver_.has_value());
    REQUIRE(motion_port_.applied_maneuver_.value() == expected_maneuver);
    REQUIRE(store_.remote_control_ == new_remote_control);
}

TEST_CASE_METHOD(
    api_fixture,
    "should skip maneuver by remote control in tracking mode",
    "[linebot]"
)
{
    auto mode = GENERATE(mode::FOLLOWING, mode::RECOVERING);

    auto new_remote_control = GENERATE(
        commands{FORWARD},
        commands{FORWARD | LEFT},
        commands{FORWARD | RIGHT},
        commands{BACKWARD},
        commands{BACKWARD | LEFT},
        commands{BACKWARD | RIGHT}
    );

    auto last_remote_control = commands{STOP};

    CAPTURE(mode, new_remote_control);

    // given
    store_.remote_control_ = last_remote_control;
    store_.mode_           = mode;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(!motion_port_.applied_maneuver_.has_value());
    REQUIRE(store_.mode_ == mode);
}

TEST_CASE_METHOD(
    api_fixture, "should skip maneuver on the same remote control", "[linebot]"
)
{
    auto new_remote_control = GENERATE(
        commands{STOP},
        commands{FORWARD},
        commands{FORWARD | LEFT},
        commands{FORWARD | RIGHT},
        commands{BACKWARD},
        commands{BACKWARD | LEFT},
        commands{BACKWARD | RIGHT}
    );

    CAPTURE(new_remote_control);

    // given
    store_.remote_control_ = new_remote_control;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(!motion_port_.applied_maneuver_.has_value());
}

} // namespace linebot
