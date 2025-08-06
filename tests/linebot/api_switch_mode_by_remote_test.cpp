#include "api_fixture.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/api.hpp"
#include "linebot/domain/mode.hpp"
#include "name_helpers.hpp"
#include <tuple>

namespace linebot
{

using mode::FOLLOWING;
using mode::LINE_DETECTED;
using mode::MANUAL;
using mode::RECOVERING;
using remote_control::BREAK;
using remote_control::FOLLOW;

TEST_CASE_METHOD(
    api_fixture, "should switch mode by remote control", "[linebot][mode]"
)
{
    auto example = GENERATE(
        std::tuple{LINE_DETECTED, remote_control{FOLLOW}, FOLLOWING},
        std::tuple{FOLLOWING, remote_control{BREAK}, MANUAL},
        std::tuple{RECOVERING, remote_control{BREAK}, MANUAL}
    );

    auto current_mode   = std::get<0>(example);
    auto remote_control = std::get<1>(example);
    auto expected_mode  = std::get<2>(example);

    CAPTURE(current_mode, remote_control, expected_mode);

    // given
    store_.mode_           = current_mode;
    store_.remote_control_ = remote_control;

    // when
    api_.switch_mode_by_remote();

    // then
    REQUIRE(status_indicator_.applied_mode_.has_value());
    CHECK(status_indicator_.applied_mode_.value() == expected_mode);
    CHECK(store_.mode_ == expected_mode);
}

TEST_CASE_METHOD(api_fixture, "should switch mode once", "[linebot][mode]")
{
    auto example = GENERATE(
        std::tuple{LINE_DETECTED, remote_control{FOLLOW}},
        std::tuple{FOLLOWING, remote_control{BREAK}},
        std::tuple{RECOVERING, remote_control{BREAK}}
    );

    auto current_mode   = std::get<0>(example);
    auto remote_control = std::get<1>(example);

    CAPTURE(current_mode, remote_control);

    // given
    status_indicator_.reset();

    store_.mode_           = current_mode;
    store_.remote_control_ = remote_control;

    // when
    api_.switch_mode_by_remote();
    api_.switch_mode_by_remote();
    api_.switch_mode_by_remote();
    api_.switch_mode_by_remote();

    // then
    CHECK(status_indicator_.apply_count_ == 1);
}

} // namespace linebot
