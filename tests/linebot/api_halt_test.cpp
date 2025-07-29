#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"

namespace linebot
{

TEST_CASE_METHOD(api_fixture, "should halt vehicle", "[linebot]")
{
    // when
    api_.halt();

    // then
    REQUIRE(motion_.applied_maneuver_.has_value());
    REQUIRE(status_indicator_.applied_mode_.has_value());

    CHECK(motion_.applied_maneuver_.value() == maneuver::none());
    CHECK(status_indicator_.applied_mode_.value() == mode::MANUAL);
    CHECK(route_guard_.stopped);
    CHECK(store_.remote_control_ == commands{commands::STOP});
}

} // namespace linebot
