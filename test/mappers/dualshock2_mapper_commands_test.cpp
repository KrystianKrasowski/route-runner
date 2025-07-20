#include "device/dualshock2.hpp"
#include "linebot/domain/commands.hpp"
#include "mapper/dualshock2_commands.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace mapper
{

using device::dualshock2;
using linebot::commands;

TEST_CASE("should map dualshock2 state to commands")
{
    using example_type = std::tuple<dualshock2::command, uint16_t>;

    auto example = GENERATE(
        example_type{dualshock2::R2, commands::FORWARD},
        example_type{dualshock2::L2, commands::BACKWARD},
        example_type{dualshock2::RIGHT, commands::RIGHT},
        example_type{dualshock2::LEFT, commands::LEFT},
        example_type{dualshock2::CIRCLE, commands::BREAK},
        example_type{dualshock2::CROSS, commands::FOLLOW}
    );

    // given
    auto dualshock2_state = std::get<0>(example);
    auto expected_command = std::get<1>(example);

    // when
    auto actual = map(dualshock2_state);

    // then
    CHECK(commands{expected_command} == actual);
}

} // namespace mapper
