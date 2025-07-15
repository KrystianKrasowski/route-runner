#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_api.hpp"
#include "linebot/motion_port.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <ostream>

namespace linebot
{

using commands::BACKWARD;
using commands::BREAK;
using commands::FORWARD;
using commands::LEFT;
using commands::NONE;
using commands::RIGHT;

using testing::AtLeast;
using testing::Eq;
using testing::TestWithParam;

struct test_params
{
    commands remote_control_;
    maneuver expected_maneuver_;

    friend std::ostream&
    operator<<(std::ostream& os, test_params params)
    {
        return os << params.remote_control_ << "; "
                  << params.expected_maneuver_;
    }
};

class motion_manual_update_test : public TestWithParam<test_params>
{
protected:

    motion_manual_update_test()
        : api_{motion_api::of(port_)}
    {
    }

    motion_port_mock port_;
    motion_api       api_;
};

TEST_P(motion_manual_update_test, should_apply_motion_by_commands)
{
    test_params params = GetParam();

    EXPECT_CALL(port_, apply(Eq(params.expected_maneuver_))).Times(AtLeast(1));

    api_.apply(params.remote_control_);
}

INSTANTIATE_TEST_SUITE_P(
    linebot,
    motion_manual_update_test,
    testing::Values(
        test_params{commands{NONE}, maneuver::none()},
        test_params{commands{FORWARD}, maneuver::forward(0)},
        test_params{commands{FORWARD | LEFT}, maneuver::forward(-50)},
        test_params{commands{FORWARD | RIGHT}, maneuver::forward(50)},
        test_params{commands{BACKWARD}, maneuver::backward(0)},
        test_params{commands{BACKWARD | LEFT}, maneuver::backward(-50)},
        test_params{commands{BACKWARD | RIGHT}, maneuver::backward(50)},
        test_params{commands{LEFT}, maneuver::none()},
        test_params{commands{RIGHT}, maneuver::none()},
        test_params{commands{BREAK}, maneuver::none()}
    )
);

} // namespace linebot
