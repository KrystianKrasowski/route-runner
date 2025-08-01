#include "device/dualshock2.hpp"
#include "linebot/domain/pid_control.hpp"
#include "mapper/dualshock2_pid_control.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace mapper
{

using device::dualshock2;
using linebot::pid_control;

TEST_CASE("should map dualshock2 state to pid control", "[mapper]")
{
    using param_type = std::tuple<uint16_t, uint8_t>;

    auto example = GENERATE(
        param_type{dualshock2::L1 | dualshock2::SQUARE, pid_control::KP_DOWN},
        param_type{dualshock2::R1 | dualshock2::SQUARE, pid_control::KP_UP},
        param_type{dualshock2::L1 | dualshock2::TRIANGLE, pid_control::KI_DOWN},
        param_type{dualshock2::R1 | dualshock2::TRIANGLE, pid_control::KI_UP},
        param_type{dualshock2::L1 | dualshock2::CIRCLE, pid_control::KD_DOWN},
        param_type{dualshock2::R1 | dualshock2::CIRCLE, pid_control::KD_UP}
    );

    // given
    uint16_t dualshock2_state = std::get<0>(example);
    uint8_t  expected_command = std::get<1>(example);

    CAPTURE(dualshock2_state, expected_command);

    // when
    auto actual = map_pid_control(dualshock2_state);

    // then
    CHECK(pid_control{expected_command} == actual);
}

} // namespace mapper
