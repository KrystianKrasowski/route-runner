#include "fixtures.h"
#include <linebot/api.h>
#include <linebot_port_mock_mode.h>
#include <linebot_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t linebot;

void
setUp(void)
{
    linebot_port_mock_mode_init();
    linebot_port_mock_motion_init();
}

void
tearDown(void)
{
    linebot_release(linebot);
}

void
should_stop(linebot_mode_t mode)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    linebot_mode_t actual_mode;
    linebot_handle_immediate_stop(linebot);
    linebot_get_mode(linebot, &actual_mode);

    // then
    linebot_mode_t applied_mode = linebot_port_mock_mode_get_changed_mode();
    TEST_ASSERT_EQUAL(LINEBOT_MODE_MANUAL, actual_mode);
    TEST_ASSERT_EQUAL(LINEBOT_MODE_MANUAL, applied_mode);
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_get_correction());
    TEST_ASSERT_EQUAL(LINEBOT_DIRECTION_NONE,
                      linebot_port_mock_motion_get_direction());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_stop, LINEBOT_MODE_MANUAL);
    RUN_PARAM_TEST(should_stop, LINEBOT_MODE_DETECTED);
    RUN_PARAM_TEST(should_stop, LINEBOT_MODE_FOLLOWING);
    RUN_PARAM_TEST(should_stop, LINEBOT_MODE_RECOVERING);

    return UNITY_END();
}
