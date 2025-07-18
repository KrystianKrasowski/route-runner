#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/mode.hpp"
#include "name_helpers.hpp"

namespace linebot
{

TEST_CASE_METHOD(api_fixture, "should switch to following mode", "[linebot]")
{
    // given
    store_.mode_ = mode::LINE_DETECTED;

    // when
    api_.attempt_mode_switch(commands{commands::FOLLOW});

    // then
    REQUIRE(store_.mode_ == mode::FOLLOWING);
    REQUIRE(status_indicator_.applied_mode_.has_value());
    REQUIRE(status_indicator_.applied_mode_.value() == mode::FOLLOWING);
}

TEST_CASE_METHOD(
    api_fixture, "should not switch to following mode", "[linebot]"
)
{
    auto remote_control = GENERATE(
        commands{commands::FORWARD},
        commands{commands::BACKWARD},
        commands{commands::BREAK},
        commands{commands::LEFT},
        commands{commands::RIGHT},
        commands{commands::FOLLOW}
    );

    CAPTURE(remote_control);

    // given
    store_.mode_ = mode::MANUAL;

    // when
    api_.attempt_mode_switch(remote_control);

    // then
    REQUIRE(store_.mode_ == mode::MANUAL);
    REQUIRE(!status_indicator_.applied_mode_.has_value());
}

TEST_CASE_METHOD(api_fixture, "should switch to manual mode", "[linebot]")
{
    auto mode = GENERATE(mode::FOLLOWING, mode::RECOVERING);

    // given
    store_.mode_ = mode;

    // when
    api_.attempt_mode_switch(commands{commands::BREAK});

    // then
    REQUIRE(store_.mode_ == mode::MANUAL);
    REQUIRE(status_indicator_.applied_mode_.has_value());
    REQUIRE(status_indicator_.applied_mode_.value() == mode::MANUAL);
}

} // namespace linebot
