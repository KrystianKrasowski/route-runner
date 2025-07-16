#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/motion_api.hpp"
#include "motion_port_mock.hpp"
#include "name_helpers.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace linebot
{

using testing::_;
using testing::TestWithParam;
using testing::Values;

class motion_manual_skip_test : public TestWithParam<commands>
{
protected:

    motion_manual_skip_test()
        : api_{motion_api::of(store_, motion_port_)}
    {
    }

    data_store       store_;
    motion_port_mock motion_port_;
    motion_api       api_;
};

TEST_P(motion_manual_skip_test, should_skip_on_same_command)
{
    commands new_commands = GetParam();

    store_.commands_ = new_commands;

    EXPECT_CALL(motion_port_, apply(_)).Times(0);

    api_.apply(new_commands);
}

INSTANTIATE_TEST_SUITE_P(
    linebot,
    motion_manual_skip_test,
    Values(
        commands{commands::NONE},
        commands{commands::FORWARD},
        commands{commands::FORWARD | commands::LEFT},
        commands{commands::FORWARD | commands::RIGHT},
        commands{commands::BACKWARD},
        commands{commands::BACKWARD | commands::LEFT},
        commands{commands::BACKWARD | commands::RIGHT}
    )
);

} // namespace linebot
