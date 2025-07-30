#include "device/dualshock2.hpp"
#include "linebot/domain/commands.hpp"
#include "mapper/dualshock2_commands.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace mapper
{

using device::dualshock2;
using linebot::command;

TEST_CASE("should map dualshock2 state to commands", "[mapper]")
{
    using param_type = std::tuple<uint16_t, uint16_t>;

    auto example = GENERATE(
        param_type{dualshock2::R2, command::FORWARD},
        param_type{dualshock2::L2, command::BACKWARD},
        param_type{dualshock2::RIGHT, command::RIGHT},
        param_type{dualshock2::LEFT, command::LEFT},
        param_type{dualshock2::CROSS, command::BREAK},
        param_type{dualshock2::START, command::FOLLOW},
        param_type{dualshock2::L1 | dualshock2::SQUARE, command::PID_KP_DOWN},
        param_type{dualshock2::R1 | dualshock2::SQUARE, command::PID_KP_UP},
        param_type{dualshock2::L1 | dualshock2::TRIANGLE, command::PID_KI_DOWN},
        param_type{dualshock2::R1 | dualshock2::TRIANGLE, command::PID_KI_UP},
        param_type{dualshock2::L1 | dualshock2::CIRCLE, command::PID_KD_DOWN},
        param_type{dualshock2::R1 | dualshock2::CIRCLE, command::PID_KD_UP}
    );


    // given
    uint16_t dualshock2_state = std::get<0>(example);
    uint16_t expected_command = std::get<1>(example);

    CAPTURE(dualshock2_state, expected_command);

    // when
    auto actual = map(dualshock2_state);

    // then
    CHECK(command{expected_command}.to_uint16()  == actual.to_uint16());
}


} // namespace mapper
