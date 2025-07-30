#include "api_fixture.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "linebot/domain/pid_control.hpp"
#include <cstdint>
#include <tuple>

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
        param_type{70, pid_control{KP_UP}, 75},
        param_type{70, pid_control{KP_DOWN}, 65}
    );

    // given
    store_.pid_params_.kp_           = std::get<0>(params);
    const auto remote_control        = std::get<1>(params);
    const auto expected_proportional = std::get<2>(params);

    // when
    api_.tune_pid_regulator(remote_control);

    // then
    CHECK(store_.pid_params_.kp_ == expected_proportional);
}

TEST_CASE_METHOD(
    api_fixture, "should tune integral parameter", "[linebot][pid]"
)
{
    SKIP();
    using param_type = std::tuple<uint16_t, pid_control, uint16_t>;

    auto params = GENERATE(
        param_type{10, pid_control{KI_UP}, 15},
        param_type{10, pid_control{KI_DOWN}, 5}
    );

    // given
    store_.pid_params_.ki_       = std::get<0>(params);
    const auto remote_control    = std::get<1>(params);
    const auto expected_integral = std::get<2>(params);

    // when
    api_.tune_pid_regulator(remote_control);

    // then
    CHECK(store_.pid_params_.ki_ == expected_integral);
}

TEST_CASE_METHOD(
    api_fixture, "should tune derivative parameter", "[linebot][pid]"
)
{
    SKIP();
    using param_type = std::tuple<uint16_t, pid_control, uint16_t>;

    auto params = GENERATE(
        param_type{410, pid_control{KD_UP}, 415},
        param_type{410, pid_control{KD_DOWN}, 405}
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
    "should not tune proportional parameter twice",
    "[linebot][pid]"
)
{
    SKIP();
    // given
    pid_control remote_control_1 =
        GENERATE(pid_control{KP_UP}, pid_control{KP_DOWN});
    pid_control remote_control_2 =
        GENERATE(pid_control{KP_UP}, pid_control{KP_DOWN});
    store_.pid_params_.kp_ = 70;

    // when
    api_.tune_pid_regulator(remote_control_1);

    uint16_t once_tunned_kp = store_.pid_params_.kp_;

    // then
    CHECK(once_tunned_kp != 70);

    // when
    api_.tune_pid_regulator(remote_control_2);

    // then
    CHECK(store_.pid_params_.kp_ == once_tunned_kp);
}

} // namespace linebot
