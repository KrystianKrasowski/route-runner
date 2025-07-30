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
    using param_type = std::tuple<uint16_t, uint16_t>;

    auto example = GENERATE(
        param_type{dualshock2::R2, motion_control::FORWARD},
        param_type{dualshock2::L2, motion_control::BACKWARD},
        param_type{dualshock2::RIGHT, motion_control::RIGHT},
        param_type{dualshock2::LEFT, motion_control::LEFT},
        param_type{dualshock2::CROSS, motion_control::BREAK},
        param_type{dualshock2::START, motion_control::FOLLOW}
    );

    // given
    uint16_t dualshock2_state = std::get<0>(example);
    uint16_t expected_command = std::get<1>(example);

    CAPTURE(dualshock2_state, expected_command);

    // when
    auto actual = map_motion_control(dualshock2_state);

    // then
    CHECK(motion_control{expected_command}.to_uint16() == actual.to_uint16());
}

} // namespace mapper
