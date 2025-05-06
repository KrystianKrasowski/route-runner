#include <devices/blink_mock.h>
#include <linebot/mode.h>
#include <linebot/port.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    device_blink_mock_init();
}

void
tearDown(void)
{
    device_blink_mock_deinit();
}

void
should_indicate_mode(linebot_mode_t mode, uint8_t expected_toggles_num)
{
    // when
    linebot_port_mode_changed(mode);
    uint8_t actual_toggles_num =
        device_blink_mock_verify_toggles_num(DEVICE_BLINK_1);

    // then
    TEST_ASSERT_EQUAL(expected_toggles_num, actual_toggles_num);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_indicate_mode, LINEBOT_MODE_MANUAL, 2);
    RUN_PARAM_TEST(should_indicate_mode, LINEBOT_MODE_DETECTED, 4);
    RUN_PARAM_TEST(should_indicate_mode, LINEBOT_MODE_FOLLOWING, 8);
    RUN_PARAM_TEST(should_indicate_mode, LINEBOT_MODE_RECOVERING, 8);

    return UNITY_END();
}
