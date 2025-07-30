#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/mode.hpp"
#include "name_helpers.hpp"
#include <tuple>

namespace linebot
{

using command::BREAK;
using command::FOLLOW;

TEST_CASE_METHOD(
    api_fixture, "should switch mode by remote control", "[linebot]"
)
{
    using test_params = std::tuple<mode, command, mode>;

    auto example = GENERATE(
        test_params{mode::LINE_DETECTED, command{FOLLOW}, mode::FOLLOWING},
        test_params{mode::FOLLOWING, command{BREAK}, mode::MANUAL},
        test_params{mode::RECOVERING, command{BREAK}, mode::MANUAL}
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

} // namespace linebot
