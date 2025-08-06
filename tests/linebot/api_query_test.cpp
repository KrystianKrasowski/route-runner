#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/remote_control.hpp"
#include "name_helpers.hpp"

namespace linebot
{

using actions::APPLY_MANEUVER;
using actions::CHANGE_MODE;
using actions::NONE;
using actions::TUNE_PID;
using remote_control::BACKWARD;
using remote_control::BREAK;
using remote_control::FOLLOW;
using remote_control::FORWARD;
using remote_control::KD_DOWN;
using remote_control::KD_UP;
using remote_control::KI_DOWN;
using remote_control::KI_UP;
using remote_control::KP_DOWN;
using remote_control::KP_UP;
using remote_control::LEFT;
using remote_control::RIGHT;
using remote_control::STOP;

TEST_CASE_METHOD(
    api_fixture,
    "should dispatch actions for remote control",
    "[linebot][dispatch]"
)
{
    auto params = GENERATE(
        std::tuple{remote_control{STOP}, APPLY_MANEUVER},
        std::tuple{remote_control{FORWARD}, APPLY_MANEUVER},
        std::tuple{remote_control{FORWARD | LEFT}, APPLY_MANEUVER},
        std::tuple{remote_control{FORWARD | RIGHT}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD | LEFT}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD | RIGHT}, APPLY_MANEUVER},
        std::tuple{remote_control{KD_DOWN}, TUNE_PID},
        std::tuple{remote_control{KD_UP}, TUNE_PID},
        std::tuple{remote_control{KI_DOWN}, TUNE_PID},
        std::tuple{remote_control{KI_UP}, TUNE_PID},
        std::tuple{remote_control{KP_DOWN}, TUNE_PID},
        std::tuple{remote_control{KP_UP}, TUNE_PID},
        std::tuple{remote_control{BREAK}, CHANGE_MODE},
        std::tuple{remote_control{FOLLOW}, CHANGE_MODE}
    );

    // given
    store_.remote_control_ = remote_control{0};
    auto commands          = std::get<0>(params);
    auto expected          = std::get<1>(params);

    // when
    auto actions = api_.query(commands);

    // then
    CHECK(actions.contain(expected));
    CHECK(store_.remote_control_ == commands);
}

TEST_CASE_METHOD(
    api_fixture,
    "should not dispatch action on same request",
    "[linebot][dispatch]"
)
{
    auto params = GENERATE(
        std::tuple{remote_control{FORWARD}, APPLY_MANEUVER},
        std::tuple{remote_control{FORWARD | LEFT}, APPLY_MANEUVER},
        std::tuple{remote_control{FORWARD | RIGHT}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD | LEFT}, APPLY_MANEUVER},
        std::tuple{remote_control{BACKWARD | RIGHT}, APPLY_MANEUVER},
        std::tuple{remote_control{KP_DOWN}, TUNE_PID},
        std::tuple{remote_control{KP_UP}, TUNE_PID},
        std::tuple{remote_control{KI_DOWN}, TUNE_PID},
        std::tuple{remote_control{KI_UP}, TUNE_PID},
        std::tuple{remote_control{KD_DOWN}, TUNE_PID},
        std::tuple{remote_control{KD_UP}, TUNE_PID},
        std::tuple{remote_control{FOLLOW}, CHANGE_MODE},
        std::tuple{remote_control{BREAK}, CHANGE_MODE}
    );

    // given
    auto    commands   = std::get<0>(params);
    auto    unexpected = std::get<1>(params);
    actions dispatched_actions{NONE};

    // when
    dispatched_actions = api_.query(commands);
    dispatched_actions = api_.query(commands);

    // then
    CHECK(!dispatched_actions.contain(unexpected));
}

TEST_CASE_METHOD(
    api_fixture,
    "should not dispatch apply maneuver by remote control while tracking",
    "[linebot][dispatcher]"
)
{
    auto commands = GENERATE(
        remote_control{FORWARD},
        remote_control{FORWARD | LEFT},
        remote_control{FORWARD | RIGHT},
        remote_control{BACKWARD},
        remote_control{BACKWARD | LEFT},
        remote_control{BACKWARD | RIGHT}
    );

    auto mode = GENERATE(mode::FOLLOWING, mode::RECOVERING);

    // given
    store_.mode_ = mode;

    // when
    auto actions = api_.query(commands);

    // then
    CHECK(!actions.contain(APPLY_MANEUVER));
}

TEST_CASE_METHOD(
    api_fixture, "should break tracking mode", "[linebot][dispatcher]"
)
{
    // given
    store_.mode_ = GENERATE(mode::FOLLOWING, mode::RECOVERING);

    // when
    auto actions = api_.query(remote_control{BREAK});

    // then
    CHECK(actions.contain(APPLY_MANEUVER));
}

} // namespace linebot
