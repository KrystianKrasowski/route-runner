#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/motion_control.hpp"
#include "name_helpers.hpp"
#include <tuple>

namespace linebot
{

using mode_control::BREAK;
using mode_control::FOLLOW;
using motion_control::STOP;

TEST_CASE_METHOD(
    api_fixture, "should switch mode by remote control", "[linebot]"
)
{
    auto example = GENERATE(
        std::tuple{mode::LINE_DETECTED, mode_control{FOLLOW}, mode::FOLLOWING},
        std::tuple{mode::FOLLOWING, mode_control{BREAK}, mode::MANUAL},
        std::tuple{mode::RECOVERING, mode_control{BREAK}, mode::MANUAL}
    );

    auto current_mode   = std::get<0>(example);
    auto remote_control = std::get<1>(example);
    auto expected_mode  = std::get<2>(example);

    CAPTURE(current_mode, remote_control, expected_mode);

    // given
    store_.mode_ = current_mode;

    // when
    api_.attempt_mode_switch(remote_control);

    // then
    REQUIRE(status_indicator_.applied_mode_.has_value());
    CHECK(status_indicator_.applied_mode_.value() == expected_mode);
    CHECK(store_.mode_ == expected_mode);
}

TEST_CASE_METHOD(
    api_fixture,
    "should clear motion control on tracking mode enter",
    "[linebot]"
)
{
    // given
    store_.mode_           = mode::LINE_DETECTED;
    store_.motion_control_ = motion_control{STOP};

    // when
    api_.attempt_mode_switch(mode_control{FOLLOW});

    // then
    CHECK(store_.motion_control_ == motion_control{STOP});
}

} // namespace linebot
