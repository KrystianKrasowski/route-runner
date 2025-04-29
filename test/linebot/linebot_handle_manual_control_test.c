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
should_change_mode(linebot_mode_t current_mode,
                   uint16_t       commands,
                   linebot_mode_t expected_mode)
{
    // given
    linebot = fixtures_linebot_acquire(current_mode);

    // when
    linebot_mode_t actual_mode;
    linebot_handle_manual_control(linebot, commands);
    linebot_get_mode(linebot, &actual_mode);

    // then
    TEST_ASSERT_EQUAL(expected_mode, linebot_port_mock_mode_get_changed_mode());
    TEST_ASSERT_EQUAL(expected_mode, actual_mode);
}

void
should_keep_mode(linebot_mode_t current_mode, uint16_t commands)
{
    // given
    linebot = fixtures_linebot_acquire(current_mode);

    // when
    linebot_mode_t actual_mode;
    linebot_handle_manual_control(linebot, commands);
    linebot_get_mode(linebot, &actual_mode);

    // then
    TEST_ASSERT_EQUAL(0, linebot_port_mock_mode_verify_changed_calls());
    TEST_ASSERT_EQUAL(current_mode, actual_mode);
}

void
should_apply_manual_motion(uint16_t            commands,
                           linebot_direction_t direction,
                           int8_t              correction)
{
    // given
    linebot = fixtures_linebot_acquire(LINEBOT_MODE_MANUAL);

    // when
    linebot_handle_manual_control(linebot, commands);

    // then
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
    TEST_ASSERT_EQUAL(direction, linebot_port_mock_motion_get_direction());
    TEST_ASSERT_EQUAL(correction, linebot_port_mock_motion_get_correction());
}

void
should_not_apply_manual_motion_while_tracking(linebot_mode_t mode,
                                              uint16_t       commands)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    linebot_handle_manual_control(linebot, commands);

    // then
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_verify_apply_calls());
}

void
should_apply_manual_motion_on_tracking_break(linebot_mode_t mode)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    linebot_handle_manual_control(linebot, LINEBOT_COMMAND_BREAK);

    // then
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
    TEST_ASSERT_EQUAL(LINEBOT_DIRECTION_NONE,
                      linebot_port_mock_motion_get_direction());
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_get_correction());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_DETECTED,
                   LINEBOT_COMMAND_FOLLOW,
                   LINEBOT_MODE_FOLLOWING);
    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_BREAK,
                   LINEBOT_MODE_MANUAL);
    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_BREAK,
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_BREAK);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_BREAK);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(
        should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD,
                   LINEBOT_DIRECTION_FORWARD,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT,
                   LINEBOT_DIRECTION_FORWARD,
                   -50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_DIRECTION_FORWARD,
                   50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD,
                   LINEBOT_DIRECTION_BACKWARD,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT,
                   LINEBOT_DIRECTION_BACKWARD,
                   -50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_DIRECTION_BACKWARD,
                   50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_FORWARD,
                   LINEBOT_DIRECTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_LEFT | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_DIRECTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_LEFT,
                   LINEBOT_DIRECTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_RIGHT,
                   LINEBOT_DIRECTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FOLLOW,
                   LINEBOT_DIRECTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BREAK,
                   LINEBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_FOLLOWING,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_tracking,
                   LINEBOT_MODE_RECOVERING,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_apply_manual_motion_on_tracking_break,
                   LINEBOT_MODE_FOLLOWING);
    RUN_PARAM_TEST(should_apply_manual_motion_on_tracking_break,
                   LINEBOT_MODE_RECOVERING);

    return UNITY_END();
}
