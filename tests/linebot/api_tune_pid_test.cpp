#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/remote_control.hpp"
#include <cstdint>
#include <tuple>

/**
 * A lot of copy/paste tests. Couldn't figured out how to pass a store PID param
 * reference to a value generator of Catch2. Maybe this is a limitation.
 * Nevertheless this is lesser evil than swith/case logic inside the tests
 */

namespace linebot
{

using remote_control::KD_DOWN;
using remote_control::KD_UP;
using remote_control::KI_DOWN;
using remote_control::KI_UP;
using remote_control::KP_DOWN;
using remote_control::KP_UP;

TEST_CASE_METHOD(
    api_fixture, "should tune proportional parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, remote_control, uint16_t>;

    auto params = GENERATE(
        param_type{700, remote_control{KP_UP}, 710},
        param_type{700, remote_control{KP_DOWN}, 690}
    );

    // given
    store_.pid_params_.kp_           = std::get<0>(params);
    store_.remote_control_           = std::get<1>(params);
    const auto expected_proportional = std::get<2>(params);

    // when
    api_.tune_pid_regulator();

    // then
    CHECK(store_.pid_params_.kp_ == expected_proportional);
}

TEST_CASE_METHOD(
    api_fixture, "should tune integral parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, remote_control, uint16_t>;

    auto params = GENERATE(
        param_type{10, remote_control{KI_UP}, 11},
        param_type{10, remote_control{KI_DOWN}, 9}
    );

    // given
    store_.pid_params_.ki_       = std::get<0>(params);
    store_.remote_control_       = std::get<1>(params);
    const auto expected_integral = std::get<2>(params);

    // when
    api_.tune_pid_regulator();

    // then
    CHECK(store_.pid_params_.ki_ == expected_integral);
}

TEST_CASE_METHOD(
    api_fixture, "should tune derivative parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, remote_control, uint16_t>;

    auto params = GENERATE(
        param_type{4100, remote_control{KD_UP}, 4200},
        param_type{4100, remote_control{KD_DOWN}, 4000}
    );

    // given
    store_.pid_params_.kd_         = std::get<0>(params);
    store_.remote_control_         = std::get<1>(params);
    const auto expected_derivative = std::get<2>(params);

    // when
    api_.tune_pid_regulator();

    // then
    CHECK(store_.pid_params_.kd_ == expected_derivative);
}

} // namespace linebot
