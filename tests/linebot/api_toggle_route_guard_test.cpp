#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"

namespace linebot
{

static const auto COORDS_ON_ROUTE  = coordinates::of_6(80, 0, 0, 0, 0, 0);
static const auto COORDS_OFF_ROUTE = coordinates::of_6(0, 0, 0, 0, 0, 0);

TEST_CASE_METHOD(api_fixture, "should start route guard", "[linebot]")
{
    // given
    store_.mode_          = mode::FOLLOWING;
    store_.line_position_ = COORDS_OFF_ROUTE;

    // when
    api_.toggle_route_guard();

    // then
    CHECK(route_guard_.started);
}

TEST_CASE_METHOD(api_fixture, "should stop route guard", "[linebot]")
{
    // given
    store_.mode_          = mode::RECOVERING;
    store_.line_position_ = COORDS_ON_ROUTE;

    // when
    api_.toggle_route_guard();

    // then
    CHECK(route_guard_.stopped);
}

} // namespace linebot
