#include <adapters.h>
#include <dualshock2.h>
#include <linebot/command.h>
#include <linebot/port.h>
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
should_map_dualshock2(uint16_t dualshock2_command, uint16_t expected_command)
{
    // when
    uint16_t actual = adapters_control_map(dualshock2_command);

    // then
    TEST_ASSERT_EQUAL(expected_command, actual);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_map_dualshock2, DS2_NONE, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_R2, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_L2, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_RIGHT, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_LEFT, LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_RIGHT,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_LEFT,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_RIGHT,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_LEFT,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CIRCLE, LINEBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CROSS, LINEBOT_COMMAND_FOLLOW);
    return UNITY_END();
}