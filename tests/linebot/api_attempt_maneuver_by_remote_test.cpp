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

constexpr auto STOP     = command::STOP;
constexpr auto FORWARD  = command::FORWARD;
constexpr auto LEFT     = command::LEFT;
constexpr auto RIGHT    = command::RIGHT;
constexpr auto BACKWARD = command::BACKWARD;

TEST_CASE_METHOD(
    api_fixture,
    "should maneuver by remote control in non-tracking mode",
    "[linebot]"
)
{
    using example_type = std::tuple<command, maneuver>;

    auto mode    = GENERATE(mode::MANUAL, mode::LINE_DETECTED);
    auto example = GENERATE(
        example_type{command{FORWARD}, maneuver::forward(0)},
        example_type{command{FORWARD | LEFT}, maneuver::forward(-50)},
        example_type{command{FORWARD | RIGHT}, maneuver::forward(50)},
        example_type{command{BACKWARD}, maneuver::backward(0)},
        example_type{command{BACKWARD | LEFT}, maneuver::backward(-50)},
        example_type{command{BACKWARD | RIGHT}, maneuver::backward(50)},
        example_type{command{LEFT}, maneuver::none()},
        example_type{command{RIGHT}, maneuver::none()},
        example_type{command{LEFT | RIGHT}, maneuver::none()}
    );

    auto new_remote_control = std::get<0>(example);
    auto expected_maneuver  = std::get<1>(example);

    CAPTURE(mode, new_remote_control, expected_maneuver);

    // given
    store_.remote_control_ = command{STOP};
    store_.mode_           = mode;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(motion_.applied_maneuver_.has_value());
    REQUIRE(motion_.applied_maneuver_.value() == expected_maneuver);
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
        command{FORWARD},
        command{FORWARD | LEFT},
        command{FORWARD | RIGHT},
        command{BACKWARD},
        command{BACKWARD | LEFT},
        command{BACKWARD | RIGHT}
    );

    auto last_remote_control = command{STOP};

    CAPTURE(mode, new_remote_control);

    // given
    store_.remote_control_ = last_remote_control;
    store_.mode_           = mode;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(!motion_.applied_maneuver_.has_value());
    REQUIRE(store_.mode_ == mode);
}

TEST_CASE_METHOD(
    api_fixture, "should skip maneuver on the same remote control", "[linebot]"
)
{
    auto new_remote_control = GENERATE(
        command{STOP},
        command{FORWARD},
        command{FORWARD | LEFT},
        command{FORWARD | RIGHT},
        command{BACKWARD},
        command{BACKWARD | LEFT},
        command{BACKWARD | RIGHT}
    );

    CAPTURE(new_remote_control);

    // given
    store_.remote_control_ = new_remote_control;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(!motion_.applied_maneuver_.has_value());
}

} // namespace linebot
