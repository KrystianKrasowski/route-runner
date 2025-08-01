#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/pid_control.hpp"
#include <cstdint>
#include <tuple>

/**
 * A lot of copy/paste tests. Couldn't figured out how to pass a store PID param
 * reference to a value generator of Catch2. Maybe this is a limitation.
 * Nevertheless this is lesser evil than swith/case logic inside the tests
 */

namespace linebot
{

using pid_control::KD_DOWN;
using pid_control::KD_UP;
using pid_control::KI_DOWN;
using pid_control::KI_UP;
using pid_control::KP_DOWN;
using pid_control::KP_UP;

TEST_CASE_METHOD(
    api_fixture, "should tune proportional parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, pid_control, uint16_t>;

    auto params = GENERATE(
        param_type{700, pid_control{KP_UP}, 710},
        param_type{700, pid_control{KP_DOWN}, 690}
    );

    // given
    store_.pid_params_.kp_           = std::get<0>(params);
    const auto control               = std::get<1>(params);
    const auto expected_proportional = std::get<2>(params);

    // when
    api_.tune_pid_regulator(control);

    // then
    CHECK(store_.pid_params_.kp_ == expected_proportional);
}

TEST_CASE_METHOD(
    api_fixture, "should tune integral parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, pid_control, uint16_t>;

    auto params = GENERATE(
        param_type{10, pid_control{KI_UP}, 11},
        param_type{10, pid_control{KI_DOWN}, 9}
    );

    // given
    store_.pid_params_.ki_       = std::get<0>(params);
    const auto control           = std::get<1>(params);
    const auto expected_integral = std::get<2>(params);

    // when
    api_.tune_pid_regulator(control);

    // then
    CHECK(store_.pid_params_.ki_ == expected_integral);
}

TEST_CASE_METHOD(
    api_fixture, "should tune derivative parameter", "[linebot][pid]"
)
{
    using param_type = std::tuple<uint16_t, pid_control, uint16_t>;

    auto params = GENERATE(
        param_type{4100, pid_control{KD_UP}, 4200},
        param_type{4100, pid_control{KD_DOWN}, 4000}
    );

    // given
    store_.pid_params_.kd_         = std::get<0>(params);
    const auto remote_control      = std::get<1>(params);
    const auto expected_derivative = std::get<2>(params);

    // when
    api_.tune_pid_regulator(remote_control);

    // then
    CHECK(store_.pid_params_.kd_ == expected_derivative);
}

TEST_CASE_METHOD(
    api_fixture,
    "should not tune proportional parameter more than once",
    "[linebot][pid]"
)
{
    // given
    auto control           = GENERATE(pid_control{KP_UP}, pid_control{KP_DOWN});
    store_.pid_params_.kp_ = 70;

    // when
    api_.tune_pid_regulator(control);
    uint16_t once_tunned_kp = store_.pid_params_.kp_;

    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);

    // then
    CHECK(store_.pid_params_.kp_ == once_tunned_kp);
}

TEST_CASE_METHOD(
    api_fixture,
    "should not tune integral parameter more than once",
    "[linebot][pid]"
)
{
    // given
    auto control           = GENERATE(pid_control{KI_UP}, pid_control{KI_DOWN});
    store_.pid_params_.ki_ = 10;

    // when
    api_.tune_pid_regulator(control);
    uint16_t once_tunned_ki = store_.pid_params_.ki_;

    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);

    // then
    CHECK(store_.pid_params_.ki_ == once_tunned_ki);
}

TEST_CASE_METHOD(
    api_fixture,
    "should not tune derivative parameter more than once",
    "[linebot][pid]"
)
{
    // given
    auto control           = GENERATE(pid_control{KD_UP}, pid_control{KD_DOWN});
    store_.pid_params_.kd_ = 410;

    // when
    api_.tune_pid_regulator(control);
    uint16_t once_tunned_kd = store_.pid_params_.kd_;

    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);
    api_.tune_pid_regulator(control);

    // then
    CHECK(store_.pid_params_.kd_ == once_tunned_kd);
}

} // namespace linebot
