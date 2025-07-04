#include <devices/blink_mock.h>
#include <devices/timeout_guard_mock.h>
#include <pathbot/domain.h>
#include <pathbot/port.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

void
setUp(void)
{
    device_blink_mock_init();
    device_timeout_guard_mock_init();
}

void
tearDown(void)
{
    device_blink_mock_deinit();
    device_timeout_guard_mock_deinit();
}

void
should_indicate_mode(pathbot_mode_t mode, uint8_t expected_sequence)
{
    // when
    pathbot_port_mode_changed(mode);
    uint8_t actual_toggles_num =
        device_blink_mock_verify_sequence(DEVICE_BLINK_1);

    // then
    TEST_ASSERT_EQUAL(expected_sequence, actual_toggles_num);
}

void
should_start_guard(pathbot_mode_t mode)
{
    // when
    pathbot_port_mode_changed(mode);

    // then
    TEST_ASSERT_TRUE(
        device_timeout_guard_mock_is_started(DEVICE_TIMEOUT_GUARD_ROUTE));
}

void
should_stop_guard(pathbot_mode_t mode)
{
    // when
    pathbot_port_mode_changed(mode);

    // then
    TEST_ASSERT_TRUE(
        device_timeout_guard_mock_is_stopped(DEVICE_TIMEOUT_GUARD_ROUTE));
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_indicate_mode, PATHBOT_MODE_MANUAL, 0x1);
    RUN_PARAM_TEST(should_indicate_mode, PATHBOT_MODE_DETECTED, 0x5);
    RUN_PARAM_TEST(should_indicate_mode, PATHBOT_MODE_FOLLOWING, 0x55);
    RUN_PARAM_TEST(should_indicate_mode, PATHBOT_MODE_RECOVERING, 0x55);

    RUN_PARAM_TEST(should_start_guard, PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_stop_guard, PATHBOT_MODE_MANUAL);
    RUN_PARAM_TEST(should_stop_guard, PATHBOT_MODE_DETECTED);
    RUN_PARAM_TEST(should_stop_guard, PATHBOT_MODE_FOLLOWING);

    return UNITY_END();
}
