#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_api.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <tuple>

namespace linebot
{

constexpr auto NONE     = commands::NONE;
constexpr auto FORWARD  = commands::FORWARD;
constexpr auto LEFT     = commands::LEFT;
constexpr auto RIGHT    = commands::RIGHT;
constexpr auto BACKWARD = commands::BACKWARD;
constexpr auto BREAK    = commands::BREAK;

struct motion_api_fixture
{
    data_store       store_;
    motion_port_mock port_;
    motion_api       api_;

    motion_api_fixture()
        : api_{motion_api::of(store_, port_)}
    {
    }
};

TEST_CASE_METHOD(motion_api_fixture, "incoming new remote control", "[linebot]")
{
    using example_type = std::tuple<commands, maneuver>;

    auto example = GENERATE(
        example_type{commands{FORWARD}, maneuver::forward(0)},
        example_type{commands{FORWARD | LEFT}, maneuver::forward(-50)},
        example_type{commands{FORWARD | RIGHT}, maneuver::forward(50)},
        example_type{commands{BACKWARD}, maneuver::backward(0)},
        example_type{commands{BACKWARD | LEFT}, maneuver::backward(-50)},
        example_type{commands{BACKWARD | RIGHT}, maneuver::backward(50)},
        example_type{commands{LEFT}, maneuver::none()},
        example_type{commands{RIGHT}, maneuver::none()},
        example_type{commands{BREAK}, maneuver::none()}
    );

    auto last_remote_control = commands{NONE};
    auto remote_control      = std::get<0>(example);
    auto expected_maneuver   = std::get<1>(example);

    GIVEN("last remote control is " << last_remote_control)
    {
        store_.remote_control_ = last_remote_control;

        WHEN("incoming remote control is " << remote_control)
        {
            api_.apply(remote_control);

            THEN("applied maneuver is " << expected_maneuver)
            {
                REQUIRE(port_.applied_maneuver_.has_value());
                REQUIRE(port_.applied_maneuver_.value() == expected_maneuver);

                AND_THEN("remote control is remembered")
                {
                    REQUIRE(store_.remote_control_ == remote_control);
                }
            }
        }
    }
}

TEST_CASE_METHOD(
    motion_api_fixture, "incoming same remote control", "[linebot]"
)
{
    auto example = GENERATE(
        commands{NONE},
        commands{FORWARD},
        commands{FORWARD | LEFT},
        commands{FORWARD | RIGHT},
        commands{BACKWARD},
        commands{BACKWARD | LEFT},
        commands{BACKWARD | RIGHT}
    );

    GIVEN("last remote control is " << example)
    {
        store_.remote_control_ = example;

        WHEN("incominf remote control is " << example)
        {
            api_.apply(example);

            THEN("maneuver is not applied")
            {
                REQUIRE(!port_.applied_maneuver_.has_value());
            }
        }
    }
}

} // namespace linebot
