#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/motion_control.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace linebot
{

constexpr auto STOP     = motion_control::STOP;
constexpr auto FORWARD  = motion_control::FORWARD;
constexpr auto LEFT     = motion_control::LEFT;
constexpr auto RIGHT    = motion_control::RIGHT;
constexpr auto BACKWARD = motion_control::BACKWARD;

TEST_CASE_METHOD(
    api_fixture,
    "should maneuver by remote control in non-tracking mode",
    "[linebot]"
)
{
    using example_type = std::tuple<motion_control, maneuver>;

    auto mode    = GENERATE(mode::MANUAL, mode::LINE_DETECTED);
    auto example = GENERATE(
        example_type{motion_control{FORWARD}, maneuver::forward(0)},
        example_type{motion_control{FORWARD | LEFT}, maneuver::forward(-50)},
        example_type{motion_control{FORWARD | RIGHT}, maneuver::forward(50)},
        example_type{motion_control{BACKWARD}, maneuver::backward(0)},
        example_type{motion_control{BACKWARD | LEFT}, maneuver::backward(-50)},
        example_type{motion_control{BACKWARD | RIGHT}, maneuver::backward(50)},
        example_type{motion_control{LEFT}, maneuver::none()},
        example_type{motion_control{RIGHT}, maneuver::none()},
        example_type{motion_control{LEFT | RIGHT}, maneuver::none()}
    );

    auto new_remote_control = std::get<0>(example);
    auto expected_maneuver  = std::get<1>(example);

    CAPTURE(mode, new_remote_control, expected_maneuver);

    // given
    store_.motion_control_ = motion_control{STOP};
    store_.mode_           = mode;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(motion_.applied_maneuver_.has_value());
    REQUIRE(motion_.applied_maneuver_.value() == expected_maneuver);
    REQUIRE(store_.motion_control_ == new_remote_control);
}

TEST_CASE_METHOD(
    api_fixture,
    "should skip maneuver by remote control in tracking mode",
    "[linebot]"
)
{
    auto mode = GENERATE(mode::FOLLOWING, mode::RECOVERING);

    auto new_remote_control = GENERATE(
        motion_control{FORWARD},
        motion_control{FORWARD | LEFT},
        motion_control{FORWARD | RIGHT},
        motion_control{BACKWARD},
        motion_control{BACKWARD | LEFT},
        motion_control{BACKWARD | RIGHT}
    );

    auto last_remote_control = motion_control{STOP};

    CAPTURE(mode, new_remote_control);

    // given
    store_.motion_control_ = last_remote_control;
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
        motion_control{STOP},
        motion_control{FORWARD},
        motion_control{FORWARD | LEFT},
        motion_control{FORWARD | RIGHT},
        motion_control{BACKWARD},
        motion_control{BACKWARD | LEFT},
        motion_control{BACKWARD | RIGHT}
    );

    CAPTURE(new_remote_control);

    // given
    store_.motion_control_ = new_remote_control;

    // when
    api_.attempt_maneuver(new_remote_control);

    // then
    REQUIRE(!motion_.applied_maneuver_.has_value());
}

} // namespace linebot
