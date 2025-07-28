#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"

namespace linebot
{

static const coordinates COORD_ON_ROUTE  = coordinates::of_6(80, 0, 0, 0, 0, 0);
static const coordinates COORD_OFF_ROUTE = coordinates::of_6(0, 0, 0, 0, 0, 0);

TEST_CASE_METHOD(api_fixture, "should start route guard", "[linebot]")
{
    // given
    store_.mode_ = mode::FOLLOWING;

    // when
    api_.attempt_route_guard_toggle(COORD_OFF_ROUTE);

    // then
    CHECK(route_guard_.started);
}

TEST_CASE_METHOD(api_fixture, "should stop route guard", "[linebot]")
{
    // given
    store_.mode_ = mode::RECOVERING;

    // when
    api_.attempt_route_guard_toggle(COORD_ON_ROUTE);

    // then
    CHECK(route_guard_.stopped);
}

} // namespace linebot
