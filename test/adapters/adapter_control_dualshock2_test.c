#include <adapters/control_dualshock2.h>
#include <devices/dualshock2.h>
#include <devices/dualshock2_mock.h>
#include <linebot/command.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

void
setUp(void)
{
    device_dualshock2_mock_init();
}

void
tearDown(void)
{
    device_dualshock2_mock_deinit();
}

void
should_read_commands(uint16_t buttons, uint16_t expected_commands)
{
    // given
    device_dualshock2_mock_set_buttons(DEVICE_DUALSHOCK2_1, buttons);

    // when
    uint16_t commands = 0;
    adapter_control_dualshock2_read(DEVICE_DUALSHOCK2_1, &commands);

    // then
    TEST_ASSERT_EQUAL(expected_commands, commands);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_read_commands, DS2_NONE, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_read_commands, DS2_R2, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_read_commands, DS2_L2, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_read_commands, DS2_RIGHT, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_read_commands, DS2_LEFT, LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_read_commands,
                   DS2_R2 | DS2_RIGHT,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_read_commands,
                   DS2_R2 | DS2_LEFT,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_read_commands,
                   DS2_L2 | DS2_RIGHT,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_read_commands,
                   DS2_L2 | DS2_LEFT,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_read_commands, DS2_CIRCLE, LINEBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_read_commands, DS2_CROSS, LINEBOT_COMMAND_FOLLOW);

    return UNITY_END();
}
