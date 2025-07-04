#include <devices/serial_mock.h>
#include <pathbot/domain.h>
#include <pathbot/port.h>
#include <string.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

void
setUp(void)
{
    device_serial_mock_init();
}

void
tearDown(void)
{
    device_serial_mock_deinit();
}

void
should_dump_mode(pathbot_mode_t mode, char *expected_msg)
{
    // given
    uint8_t const length = strlen(expected_msg) + 1;

    // when
    pathbot_port_dump_mode(mode);
    char *actual_msg = device_serial_mock_get_applied_msg(DEVICE_SERIAL_1);

    // then
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_msg, actual_msg, length);
}

void
should_dump_pid_config(void)
{
    // given
    pathbot_pid_conf_t pid_conf = {
        .kp = 0.6,
        .ki = 0,
        .kd = 3.2,
    };

    char *expected_msg = "PID: kp 60; ki 0; kd 320\n\r";
    int   length       = strlen(expected_msg);

    // when
    pathbot_port_dump_pid_conf(&pid_conf);
    char *actual_msg = device_serial_mock_get_applied_msg(DEVICE_SERIAL_1);

    // then
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_msg, actual_msg, length);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_MANUAL, "MODE: manual\n\r");
    RUN_PARAM_TEST(
        should_dump_mode, PATHBOT_MODE_DETECTED, "MODE: detected\n\r");
    RUN_PARAM_TEST(
        should_dump_mode, PATHBOT_MODE_RECOVERING, "MODE: recovering\n\r");
    RUN_PARAM_TEST(
        should_dump_mode, PATHBOT_MODE_FOLLOWING, "MODE: following\n\r");

    RUN_TEST(should_dump_pid_config);

    return UNITY_END();
}
