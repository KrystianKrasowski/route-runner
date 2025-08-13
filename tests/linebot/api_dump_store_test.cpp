#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <etl/string.h>

namespace linebot
{

TEST_CASE_METHOD(api_fixture, "should dump mode", "[linebot]")
{
    auto params = GENERATE(
        std::tuple{mode::MANUAL, "Mode: 0"},
        std::tuple{mode::LINE_DETECTED, "Mode: 1"},
        std::tuple{mode::FOLLOWING, "Mode: 2"},
        std::tuple{mode::RECOVERING, "Mode: 3"}
    );

    auto mode    = std::get<0>(params);
    auto outcome = std::get<1>(params);

    // given
    store_.mode_ = mode;

    // when
    info_string dump_buffer;
    api_.dump_store(dump_buffer);

    // then
    CAPTURE(outcome, dump_buffer);

    CHECK(dump_buffer.contains(outcome));
}

TEST_CASE_METHOD(api_fixture, "should dump PID", "[linebot]")
{
    // given
    store_.pid_params_.kp_ = 640;
    store_.pid_params_.ki_ = 2;
    store_.pid_params_.kd_ = 4200;

    // when
    info_string dump_buffer;
    api_.dump_store(dump_buffer);

    // then
    CAPTURE(dump_buffer);

    CHECK(dump_buffer.contains("PID: kp 640, ki 2, kd 4200"));
}

} // namespace linebot
