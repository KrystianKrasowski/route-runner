#include "adapter/motion_l293.hpp"
#include "device/l293.hpp"
#include "linebot/domain/maneuver.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstdint>
#include <device/l293_mock.hpp>
#include <tuple>

namespace adapter
{

using device::l293;
using linebot::maneuver;

TEST_CASE("should apply motion", "[adapter][motion][l293]")
{

    device::l293_mock motor_left;
    device::l293_mock motor_right;

    auto adapter = motion_l293::of(motor_left, motor_right);

    SECTION("left motor")
    {
        using example_type = std::tuple<maneuver, uint8_t, l293::rotation>;

        auto example = GENERATE(
            example_type{maneuver::forward(-100), 100, l293::LEFT},
            example_type{maneuver::forward(-90), 80, l293::LEFT},
            example_type{maneuver::forward(-80), 60, l293::LEFT},
            example_type{maneuver::forward(-70), 40, l293::LEFT},
            example_type{maneuver::forward(-60), 20, l293::LEFT},
            example_type{maneuver::forward(-50), 0, l293::NONE},
            example_type{maneuver::forward(-40), 20, l293::RIGHT},
            example_type{maneuver::forward(-30), 40, l293::RIGHT},
            example_type{maneuver::forward(-20), 60, l293::RIGHT},
            example_type{maneuver::forward(-10), 80, l293::RIGHT},
            example_type{maneuver::forward(0), 100, l293::RIGHT},
            example_type{maneuver::forward(10), 100, l293::RIGHT},
            example_type{maneuver::forward(20), 100, l293::RIGHT},
            example_type{maneuver::forward(30), 100, l293::RIGHT},
            example_type{maneuver::forward(40), 100, l293::RIGHT},
            example_type{maneuver::forward(50), 100, l293::RIGHT},
            example_type{maneuver::forward(60), 100, l293::RIGHT},
            example_type{maneuver::forward(70), 100, l293::RIGHT},
            example_type{maneuver::forward(80), 100, l293::RIGHT},
            example_type{maneuver::forward(90), 100, l293::RIGHT},
            example_type{maneuver::forward(100), 100, l293::RIGHT},
            example_type{maneuver::backward(-100), 100, l293::RIGHT},
            example_type{maneuver::backward(-90), 80, l293::RIGHT},
            example_type{maneuver::backward(-80), 60, l293::RIGHT},
            example_type{maneuver::backward(-70), 40, l293::RIGHT},
            example_type{maneuver::backward(-60), 20, l293::RIGHT},
            example_type{maneuver::backward(-50), 0, l293::NONE},
            example_type{maneuver::backward(-40), 20, l293::LEFT},
            example_type{maneuver::backward(-30), 40, l293::LEFT},
            example_type{maneuver::backward(-20), 60, l293::LEFT},
            example_type{maneuver::backward(-10), 80, l293::LEFT},
            example_type{maneuver::backward(0), 100, l293::LEFT},
            example_type{maneuver::backward(10), 100, l293::LEFT},
            example_type{maneuver::backward(20), 100, l293::LEFT},
            example_type{maneuver::backward(30), 100, l293::LEFT},
            example_type{maneuver::backward(40), 100, l293::LEFT},
            example_type{maneuver::backward(50), 100, l293::LEFT},
            example_type{maneuver::backward(60), 100, l293::LEFT},
            example_type{maneuver::backward(70), 100, l293::LEFT},
            example_type{maneuver::backward(80), 100, l293::LEFT},
            example_type{maneuver::backward(90), 100, l293::LEFT},
            example_type{maneuver::backward(100), 100, l293::LEFT}
        );

        auto motion     = std::get<0>(example);
        auto duty_cycle = std::get<1>(example);
        auto rotation   = std::get<2>(example);

        // when
        adapter.apply(motion);

        // then
        CHECK(motor_left.applied_duty_cycle_.has_value());
        CHECK(motor_left.applied_duty_cycle_.value() == duty_cycle);
        CHECK(motor_left.applied_rotation_.has_value());
        CHECK(motor_left.applied_rotation_.value() == rotation);
    }

    SECTION("right motor")
    {
        using example_type = std::tuple<maneuver, uint8_t, l293::rotation>;

        auto example = GENERATE(
            example_type{maneuver::forward(-100), 100, l293::RIGHT},
            example_type{maneuver::forward(-90), 100, l293::RIGHT},
            example_type{maneuver::forward(-80), 100, l293::RIGHT},
            example_type{maneuver::forward(-70), 100, l293::RIGHT},
            example_type{maneuver::forward(-60), 100, l293::RIGHT},
            example_type{maneuver::forward(-50), 100, l293::RIGHT},
            example_type{maneuver::forward(-40), 100, l293::RIGHT},
            example_type{maneuver::forward(-30), 100, l293::RIGHT},
            example_type{maneuver::forward(-20), 100, l293::RIGHT},
            example_type{maneuver::forward(-10), 100, l293::RIGHT},
            example_type{maneuver::forward(0), 100, l293::RIGHT},
            example_type{maneuver::forward(10), 80, l293::RIGHT},
            example_type{maneuver::forward(20), 60, l293::RIGHT},
            example_type{maneuver::forward(30), 40, l293::RIGHT},
            example_type{maneuver::forward(40), 20, l293::RIGHT},
            example_type{maneuver::forward(50), 0, l293::NONE},
            example_type{maneuver::forward(60), 20, l293::LEFT},
            example_type{maneuver::forward(70), 40, l293::LEFT},
            example_type{maneuver::forward(80), 60, l293::LEFT},
            example_type{maneuver::forward(90), 80, l293::LEFT},
            example_type{maneuver::forward(100), 100, l293::LEFT},
            example_type{maneuver::backward(-100), 100, l293::LEFT},
            example_type{maneuver::backward(-90), 100, l293::LEFT},
            example_type{maneuver::backward(-80), 100, l293::LEFT},
            example_type{maneuver::backward(-70), 100, l293::LEFT},
            example_type{maneuver::backward(-60), 100, l293::LEFT},
            example_type{maneuver::backward(-50), 100, l293::LEFT},
            example_type{maneuver::backward(-40), 100, l293::LEFT},
            example_type{maneuver::backward(-30), 100, l293::LEFT},
            example_type{maneuver::backward(-20), 100, l293::LEFT},
            example_type{maneuver::backward(-10), 100, l293::LEFT},
            example_type{maneuver::backward(0), 100, l293::LEFT},
            example_type{maneuver::backward(10), 80, l293::LEFT},
            example_type{maneuver::backward(20), 60, l293::LEFT},
            example_type{maneuver::backward(30), 40, l293::LEFT},
            example_type{maneuver::backward(40), 20, l293::LEFT},
            example_type{maneuver::backward(50), 0, l293::NONE},
            example_type{maneuver::backward(60), 20, l293::RIGHT},
            example_type{maneuver::backward(70), 40, l293::RIGHT},
            example_type{maneuver::backward(80), 60, l293::RIGHT},
            example_type{maneuver::backward(90), 80, l293::RIGHT},
            example_type{maneuver::backward(100), 100, l293::RIGHT}
        );

        auto           motion     = std::get<0>(example);
        int8_t         duty_cycle = std::get<1>(example);
        l293::rotation rotation   = std::get<2>(example);

        // when
        adapter.apply(motion);

        // then
        CHECK(motor_right.applied_duty_cycle_.has_value());
        CHECK(motor_right.applied_duty_cycle_.value() == duty_cycle);
        CHECK(motor_right.applied_rotation_.has_value());
        CHECK(motor_right.applied_rotation_.value() == rotation);
    }
}

} // namespace adapter
