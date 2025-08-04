#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/remote_control.hpp"

namespace linebot
{

using actions::APPLY_MANEUVER;
using actions::TUNE_PID;
using actions::CHANGE_MODE;
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

TEST_CASE_METHOD(
    api_fixture,
    "should dispatch actions for remote control",
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
    auto commands = std::get<0>(params);
    auto expected = std::get<1>(params);

    // when
    auto actions = api_.dispatch(commands);

    // then
    CHECK(actions.contain(expected));
}

} // namespace linebot
