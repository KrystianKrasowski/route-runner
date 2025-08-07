#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "device/dualshock2.hpp"
#include "linebot/domain/remote_control.hpp"
#include "mapper/dualshock2_remote_control.hpp"
#include <tuple>

namespace mapper
{

using device::dualshock2;
using linebot::remote_control;

TEST_CASE("should map dualshock2 state to remote control", "[mapper]")
{
    using param_type = std::tuple<uint16_t, uint16_t>;
    
    auto example = GENERATE(
        param_type{dualshock2::R2, remote_control::FORWARD},
        param_type{dualshock2::L2, remote_control::BACKWARD},
        param_type{dualshock2::RIGHT, remote_control::RIGHT},
        param_type{dualshock2::LEFT, remote_control::LEFT},
        param_type{
            dualshock2::L1 | dualshock2::SQUARE, remote_control::KP_DOWN
        },
        param_type{dualshock2::R1 | dualshock2::SQUARE, remote_control::KP_UP},
        param_type{
            dualshock2::L1 | dualshock2::TRIANGLE, remote_control::KI_DOWN
        },
        param_type{
            dualshock2::R1 | dualshock2::TRIANGLE, remote_control::KI_UP
        },
        param_type{
            dualshock2::L1 | dualshock2::CIRCLE, remote_control::KD_DOWN
        },
        param_type{dualshock2::R1 | dualshock2::CIRCLE, remote_control::KD_UP},
        param_type{dualshock2::START, remote_control::FOLLOW},
        param_type{dualshock2::CROSS, remote_control::BREAK}
    );

    // given
    uint16_t dualshock2_state = std::get<0>(example);
    uint16_t  expected_command = std::get<1>(example);

    CAPTURE(dualshock2_state, expected_command);

    // when
    auto actual = map_remote_control(dualshock2_state);

    // then
    CHECK(remote_control{expected_command} == actual);
}

} // namespace mapper
