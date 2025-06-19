#include <devices/dualshock2.h>
#include <devices/dualshock2_mock.h>
#include <mappers/dualshock2_control.h>
#include <pathbot/domain.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_map_dualshock2(uint16_t dualshock2_state, uint16_t expected_commands)
{
    // when
    uint16_t actual_commands = mapper_dualshock2_control_read(dualshock2_state);

    // then
    TEST_ASSERT_EQUAL(expected_commands, actual_commands);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_map_dualshock2, DS2_NONE, PATHBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_R2, PATHBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_L2, PATHBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_RIGHT, PATHBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_LEFT, PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_RIGHT,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_LEFT,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_RIGHT,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_LEFT,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CIRCLE, PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CROSS, PATHBOT_COMMAND_FOLLOW);

    return UNITY_END();
}
