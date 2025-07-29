#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

namespace linebot
{

TEST_CASE_METHOD(api_fixture, "should dump mode", "[linebot]")
{
    // given
    store_.mode_ = GENERATE(
        mode::MANUAL, mode::LINE_DETECTED, mode::FOLLOWING, mode::RECOVERING
    );

    // when
    api_.dump_store();

    // then
    REQUIRE(printer_.printed_mode_.has_value());
    CHECK(printer_.printed_mode_.value() == store_.mode_);
}

TEST_CASE_METHOD(api_fixture, "should dump PID", "[linebot]")
{
    // when
    api_.dump_store();

    // then
    REQUIRE(printer_.printed_pid_params_.has_value());
    CHECK(printer_.printed_pid_params_.value() == store_.pid_params_);
}

} // namespace linebot
