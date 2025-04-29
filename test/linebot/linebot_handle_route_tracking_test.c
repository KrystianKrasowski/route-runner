#include "fixtures.h"
#include <linebot/api.h>
#include <linebot_port_mock_mode.h>
#include <linebot_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t        linebot;
static linebot_coords_t new_coords;

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
    linebot_coords_release(new_coords);
}

void
should_change_mode(linebot_mode_t         current_mode,
                   fixtures_coords_type_t coords_type,
                   linebot_mode_t         expected_mode)
{
    // given
    linebot    = fixtures_linebot_acquire(current_mode);
    new_coords = fixtures_coords_acquire(coords_type);

    // when
    linebot_mode_t actual_mode;
    linebot_handle_route_tracking(linebot, new_coords);
    linebot_get_mode(linebot, &actual_mode);

    // then
    linebot_mode_t applied_mode = linebot_port_mock_mode_get_changed_mode();
    TEST_ASSERT_EQUAL(expected_mode, actual_mode);
    TEST_ASSERT_EQUAL(expected_mode, applied_mode);
    TEST_ASSERT_EQUAL(1, linebot_port_mock_mode_verify_changed_calls());
}

void
should_keep_mode(linebot_mode_t mode, fixtures_coords_type_t coords_type)
{
    // given
    linebot    = fixtures_linebot_acquire(mode);
    new_coords = fixtures_coords_acquire(coords_type);

    // when
    linebot_mode_t actual_mode;
    linebot_handle_route_tracking(linebot, new_coords);
    linebot_get_mode(linebot, &actual_mode);

    // then
    TEST_ASSERT_EQUAL(mode, actual_mode);
    TEST_ASSERT_EQUAL(0, linebot_port_mock_mode_verify_changed_calls());
}

void
should_apply_following_motion(linebot_mode_t mode, int calls)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    new_coords = fixtures_coords_acquire(COORDS_ON_ROUTE);
    linebot_handle_route_tracking(linebot, new_coords);

    // then
    TEST_ASSERT_EQUAL(calls, linebot_port_mock_motion_verify_apply_calls());
}

void
should_finish_tracking(void)
{
    // given
    linebot = fixtures_linebot_acquire(LINEBOT_MODE_FOLLOWING);

    // when
    new_coords = fixtures_coords_acquire(COORDS_ON_FINISH);
    linebot_handle_route_tracking(linebot, new_coords);

    // then
    TEST_ASSERT_EQUAL(LINEBOT_DIRECTION_NONE,
                      linebot_port_mock_motion_get_direction());
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_get_correction());
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
}

void
should_not_finish_in_manual_mode(void)
{
    // given
    linebot = fixtures_linebot_acquire(LINEBOT_MODE_MANUAL);

    // when
    new_coords = fixtures_coords_acquire(COORDS_ON_FINISH);
    linebot_handle_route_tracking(linebot, new_coords);

    // then
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_verify_apply_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_MANUAL,
                   COORDS_ON_ROUTE,
                   LINEBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_DETECTED,
                   COORDS_OFF_ROUTE,
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_FOLLOWING,
                   COORDS_OFF_ROUTE,
                   LINEBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_RECOVERING,
                   COORDS_ON_ROUTE,
                   LINEBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_FOLLOWING,
                   COORDS_ON_FINISH,
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_RECOVERING,
                   COORDS_ON_FINISH,
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, COORDS_OFF_ROUTE);

    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, COORDS_ON_ROUTE);

    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, COORDS_ON_ROUTE);

    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, COORDS_OFF_ROUTE);

    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_FOLLOWING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_RECOVERING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_DETECTED, 0);
    RUN_PARAM_TEST(should_apply_following_motion, LINEBOT_MODE_MANUAL, 0);

    RUN_TEST(should_finish_tracking);
    RUN_TEST(should_not_finish_in_manual_mode);

    return UNITY_END();
}
