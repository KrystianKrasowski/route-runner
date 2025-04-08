#include "fixtures.h"
#include <linebot.h>
#include <linebot_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t linebot;

void
setUp(void)
{
    linebot_port_mock_motion_init();
    linebot_init();
}

void
tearDown(void)
{
}

void
should_apply_manual_motion(uint16_t                   commands,
                           linebot_motion_direction_t direction,
                           int8_t                     correction)
{
    // given
    linebot = linebot_fixture_acquire(LINEBOT_MODE_MANUAL);

    // when
    linebot_apply_manual_motion(linebot, commands);

    // then
    linebot_motion_t actual = linebot_port_mock_motion_get_applied();
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
    TEST_ASSERT_EQUAL(direction, linebot_get_motion_direction(actual));
    TEST_ASSERT_EQUAL(correction, linebot_get_motion_correction(actual));
}

void
should_not_apply_manual_motion_while_tracking(linebot_mode_t mode,
                                              uint16_t       commands)
{
    // given
    linebot = linebot_fixture_acquire(mode);

    // when
    linebot_apply_manual_motion(linebot, commands);

    // then
    TEST_ASSERT_EQUAL(0, linebot_port_mock_motion_verify_apply_calls());
}

void
should_apply_manual_motion_on_tracking_break(linebot_mode_t mode)
{
    // given
    linebot = linebot_fixture_acquire(mode);

    // when
    linebot_apply_manual_motion(linebot, LINEBOT_COMMAND_BREAK);

    // then
    linebot_motion_t actual = linebot_port_mock_motion_get_applied();
    TEST_ASSERT_EQUAL(1, linebot_port_mock_motion_verify_apply_calls());
    TEST_ASSERT_EQUAL(LINEBOT_MOTION_NONE,
                      linebot_get_motion_direction(actual));
    TEST_ASSERT_EQUAL(0, linebot_get_motion_correction(actual));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD,
                   LINEBOT_MOTION_FORWARD,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_LEFT,
                   LINEBOT_MOTION_FORWARD,
                   -50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FORWARD | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_MOTION_FORWARD,
                   50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD,
                   LINEBOT_MOTION_BACKWARD,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_LEFT,
                   LINEBOT_MOTION_BACKWARD,
                   -50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_MOTION_BACKWARD,
                   50);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BACKWARD | LINEBOT_COMMAND_FORWARD,
                   LINEBOT_MOTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_LEFT | LINEBOT_COMMAND_RIGHT,
                   LINEBOT_MOTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_LEFT,
                   LINEBOT_MOTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_RIGHT,
                   LINEBOT_MOTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_FOLLOW,
                   LINEBOT_MOTION_NONE,
                   0);
    RUN_PARAM_TEST(should_apply_manual_motion,
                   LINEBOT_COMMAND_BREAK,
                   LINEBOT_MOTION_NONE,
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