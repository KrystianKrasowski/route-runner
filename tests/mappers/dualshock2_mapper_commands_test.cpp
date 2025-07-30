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
    using example_type = std::tuple<dualshock2::command, uint16_t>;

    auto example = GENERATE(
        example_type{dualshock2::R2, command::FORWARD},
        example_type{dualshock2::L2, command::BACKWARD},
        example_type{dualshock2::RIGHT, command::RIGHT},
        example_type{dualshock2::LEFT, command::LEFT},
        example_type{dualshock2::CROSS, command::BREAK},
        example_type{dualshock2::START, command::FOLLOW}
    );

    // given
    auto dualshock2_state = std::get<0>(example);
    auto expected_command = std::get<1>(example);

    // when
    auto actual = map(dualshock2_state);

    // then
    CHECK(command{expected_command} == actual);
}

} // namespace mapper
