#include "device/dualshock2.hpp"
#include "linebot/domain/motion_control.hpp"
#include "mapper/dualshock2_motion_control.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace mapper
{

using device::dualshock2;
using linebot::motion_control;

TEST_CASE("should map dualshock2 state to motion control", "[mapper]")
{
    auto example = GENERATE(
        std::tuple{dualshock2::R2, motion_control::FORWARD},
        std::tuple{dualshock2::L2, motion_control::BACKWARD},
        std::tuple{dualshock2::RIGHT, motion_control::RIGHT},
        std::tuple{dualshock2::LEFT, motion_control::LEFT}
    );

    // given
    uint16_t dualshock2_state = std::get<0>(example);
    uint8_t expected_command = std::get<1>(example);

    CAPTURE(dualshock2_state, expected_command);

    // when
    auto actual = map_motion_control(dualshock2_state);

    // then
    CHECK(motion_control{expected_command} == actual);
}

} // namespace mapper
