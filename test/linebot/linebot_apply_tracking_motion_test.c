#include "fixtures.h"
#include <linebot/api.h>
#include <linebot_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t        linebot;
static linebot_coords_t new_coords;

void
setUp(void)
{
    linebot_port_mock_motion_init();
}

void
tearDown(void)
{
    linebot_release(linebot);
    linebot_coords_release(new_coords);
}

void
should_apply_following_motion(linebot_mode_t mode, int calls)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    new_coords = fixtures_coords_acquire(COORDS_ON_ROUTE);
    linebot_apply_tracking_motion(linebot, new_coords);

    // then
    TEST_ASSERT_EQUAL(calls, linebot_port_mock_motion_verify_apply_calls());
}

void
should_finish_tracking(void)
{
    // given
    linebot = fixtures_linebot_acquire(LINEBOT_MODE_MANUAL);

    // when
    new_coords = fixtures_coords_acquire(COORDS_ON_FINISH);
    linebot_apply_tracking_motion(linebot, new_coords);

    // then
    TEST_ASSERT_EQUAL(LINEBOT_MOTION_NONE,
                      linebot_port_mock_motion_get_direction());
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_get_correction());
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_FOLLOWING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_RECOVERING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_DETECTED, 0);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_MANUAL, 0);

    RUN_TEST(should_finish_tracking);

    return UNITY_END();
}