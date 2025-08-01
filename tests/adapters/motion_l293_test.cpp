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

    SECTION("left motor duty cycle characteristic")
    {
        auto direction = GENERATE(maneuver::FORWARD, maneuver::BACKWARD);

        auto param = GENERATE(
            std::tuple{-100, 100},
            std::tuple{-90, 80},
            std::tuple{-80, 60},
            std::tuple{-70, 40},
            std::tuple{-60, 20},
            std::tuple{-50, 0},
            std::tuple{-40, 20},
            std::tuple{-30, 40},
            std::tuple{-20, 60},
            std::tuple{-10, 80},
            std::tuple{-9, 100},
            std::tuple{-8, 100},
            std::tuple{-7, 100},
            std::tuple{-6, 100},
            std::tuple{-5, 100},
            std::tuple{-4, 100},
            std::tuple{-3, 100},
            std::tuple{-2, 100},
            std::tuple{-1, 100},
            std::tuple{0, 100},
            std::tuple{10, 100},
            std::tuple{20, 100},
            std::tuple{30, 100},
            std::tuple{40, 100},
            std::tuple{50, 100},
            std::tuple{60, 100},
            std::tuple{70, 100},
            std::tuple{80, 100},
            std::tuple{90, 100},
            std::tuple{100, 100}
        );

        // given
        int8_t  correction = std::get<0>(param);
        uint8_t duty_cycle = std::get<1>(param);

        maneuver motion{direction, correction};

        // when
        adapter.apply(motion);

        // then
        REQUIRE(motor_left.applied_duty_cycle_.has_value());
        CHECK(motor_left.applied_duty_cycle_.value() == duty_cycle);
    }

    SECTION("left motor spinning direction")
    {
        auto param = GENERATE(
            std::tuple{maneuver::forward(-100), l293::LEFT},
            std::tuple{maneuver::forward(-90), l293::LEFT},
            std::tuple{maneuver::forward(-80), l293::LEFT},
            std::tuple{maneuver::forward(-70), l293::LEFT},
            std::tuple{maneuver::forward(-60), l293::LEFT},
            std::tuple{maneuver::forward(-50), l293::NONE},
            std::tuple{maneuver::forward(-40), l293::RIGHT},
            std::tuple{maneuver::forward(-30), l293::RIGHT},
            std::tuple{maneuver::forward(-20), l293::RIGHT},
            std::tuple{maneuver::forward(-10), l293::RIGHT},
            std::tuple{maneuver::forward(0), l293::RIGHT},
            std::tuple{maneuver::forward(10), l293::RIGHT},
            std::tuple{maneuver::forward(20), l293::RIGHT},
            std::tuple{maneuver::forward(30), l293::RIGHT},
            std::tuple{maneuver::forward(40), l293::RIGHT},
            std::tuple{maneuver::forward(50), l293::RIGHT},
            std::tuple{maneuver::forward(60), l293::RIGHT},
            std::tuple{maneuver::forward(70), l293::RIGHT},
            std::tuple{maneuver::forward(80), l293::RIGHT},
            std::tuple{maneuver::forward(90), l293::RIGHT},
            std::tuple{maneuver::forward(100), l293::RIGHT},

            std::tuple{maneuver::backward(-100), l293::RIGHT},
            std::tuple{maneuver::backward(-90), l293::RIGHT},
            std::tuple{maneuver::backward(-80), l293::RIGHT},
            std::tuple{maneuver::backward(-70), l293::RIGHT},
            std::tuple{maneuver::backward(-60), l293::RIGHT},
            std::tuple{maneuver::backward(-50), l293::NONE},
            std::tuple{maneuver::backward(-40), l293::LEFT},
            std::tuple{maneuver::backward(-30), l293::LEFT},
            std::tuple{maneuver::backward(-20), l293::LEFT},
            std::tuple{maneuver::backward(-10), l293::LEFT},
            std::tuple{maneuver::backward(0), l293::LEFT},
            std::tuple{maneuver::backward(10), l293::LEFT},
            std::tuple{maneuver::backward(20), l293::LEFT},
            std::tuple{maneuver::backward(30), l293::LEFT},
            std::tuple{maneuver::backward(40), l293::LEFT},
            std::tuple{maneuver::backward(50), l293::LEFT},
            std::tuple{maneuver::backward(60), l293::LEFT},
            std::tuple{maneuver::backward(70), l293::LEFT},
            std::tuple{maneuver::backward(80), l293::LEFT},
            std::tuple{maneuver::backward(90), l293::LEFT},
            std::tuple{maneuver::backward(100), l293::LEFT}
        );

        // given
        auto maneuver = std::get<0>(param);
        auto rotation = std::get<1>(param);

        // when
        adapter.apply(maneuver);

        // then
        REQUIRE(motor_left.applied_rotation_.has_value());
        CHECK(motor_left.applied_rotation_.value() == rotation);
    }

    SECTION("right motor duty cycle characteristic")
    {
        auto direction = GENERATE(maneuver::FORWARD, maneuver::BACKWARD);

        auto param = GENERATE(
            std::tuple{-100, 100},
            std::tuple{-90, 100},
            std::tuple{-80, 100},
            std::tuple{-70, 100},
            std::tuple{-60, 100},
            std::tuple{-50, 100},
            std::tuple{-40, 100},
            std::tuple{-30, 100},
            std::tuple{-20, 100},
            std::tuple{-10, 100},
            std::tuple{0, 100},
            std::tuple{1, 100},
            std::tuple{2, 100},
            std::tuple{3, 100},
            std::tuple{4, 100},
            std::tuple{5, 100},
            std::tuple{6, 100},
            std::tuple{7, 100},
            std::tuple{8, 100},
            std::tuple{9, 100},
            std::tuple{10, 80},
            std::tuple{20, 60},
            std::tuple{30, 40},
            std::tuple{40, 20},
            std::tuple{50, 0},
            std::tuple{60, 20},
            std::tuple{70, 40},
            std::tuple{80, 60},
            std::tuple{90, 80},
            std::tuple{100, 100}
        );

        // given
        int8_t  correction = std::get<0>(param);
        uint8_t duty_cycle = std::get<1>(param);

        maneuver motion{direction, correction};

        // when
        adapter.apply(motion);

        // then
        REQUIRE(motor_right.applied_duty_cycle_.has_value());
        CHECK(motor_right.applied_duty_cycle_.value() == duty_cycle);
    }

    SECTION("right motor spinning direction")
    {
        auto param = GENERATE(
            std::tuple{maneuver::forward(-100), l293::RIGHT},
            std::tuple{maneuver::forward(-90), l293::RIGHT},
            std::tuple{maneuver::forward(-80), l293::RIGHT},
            std::tuple{maneuver::forward(-70), l293::RIGHT},
            std::tuple{maneuver::forward(-60), l293::RIGHT},
            std::tuple{maneuver::forward(-50), l293::RIGHT},
            std::tuple{maneuver::forward(-40), l293::RIGHT},
            std::tuple{maneuver::forward(-30), l293::RIGHT},
            std::tuple{maneuver::forward(-20), l293::RIGHT},
            std::tuple{maneuver::forward(-10), l293::RIGHT},
            std::tuple{maneuver::forward(0), l293::RIGHT},
            std::tuple{maneuver::forward(10), l293::RIGHT},
            std::tuple{maneuver::forward(20), l293::RIGHT},
            std::tuple{maneuver::forward(30), l293::RIGHT},
            std::tuple{maneuver::forward(40), l293::RIGHT},
            std::tuple{maneuver::forward(50), l293::NONE},
            std::tuple{maneuver::forward(60), l293::LEFT},
            std::tuple{maneuver::forward(70), l293::LEFT},
            std::tuple{maneuver::forward(80), l293::LEFT},
            std::tuple{maneuver::forward(90), l293::LEFT},
            std::tuple{maneuver::forward(100), l293::LEFT},

            std::tuple{maneuver::backward(-100), l293::LEFT},
            std::tuple{maneuver::backward(-90), l293::LEFT},
            std::tuple{maneuver::backward(-80), l293::LEFT},
            std::tuple{maneuver::backward(-70), l293::LEFT},
            std::tuple{maneuver::backward(-60), l293::LEFT},
            std::tuple{maneuver::backward(-50), l293::LEFT},
            std::tuple{maneuver::backward(-40), l293::LEFT},
            std::tuple{maneuver::backward(-30), l293::LEFT},
            std::tuple{maneuver::backward(-20), l293::LEFT},
            std::tuple{maneuver::backward(-10), l293::LEFT},
            std::tuple{maneuver::backward(0), l293::LEFT},
            std::tuple{maneuver::backward(10), l293::LEFT},
            std::tuple{maneuver::backward(20), l293::LEFT},
            std::tuple{maneuver::backward(30), l293::LEFT},
            std::tuple{maneuver::backward(40), l293::LEFT},
            std::tuple{maneuver::backward(50), l293::NONE},
            std::tuple{maneuver::backward(60), l293::RIGHT},
            std::tuple{maneuver::backward(70), l293::RIGHT},
            std::tuple{maneuver::backward(80), l293::RIGHT},
            std::tuple{maneuver::backward(90), l293::RIGHT},
            std::tuple{maneuver::backward(100), l293::RIGHT}
        );

        // given
        auto maneuver = std::get<0>(param);
        auto rotation = std::get<1>(param);

        // when
        adapter.apply(maneuver);

        // then
        REQUIRE(motor_right.applied_rotation_.has_value());
        CHECK(motor_right.applied_rotation_.value() == rotation);
    }
}

} // namespace adapter
