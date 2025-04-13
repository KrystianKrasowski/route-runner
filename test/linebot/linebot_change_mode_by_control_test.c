#include "fixtures.h"
#include <linebot/api.h>
#include <linebot_port_mock_mode.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t linebot;

void
setUp(void)
{
    linebot_port_mock_mode_init();
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
    linebot_change_mode_by_control(linebot, commands);
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
    linebot_change_mode_by_control(linebot, commands);
    linebot_get_mode(linebot, &actual_mode);

    // then
    TEST_ASSERT_EQUAL(0, linebot_port_mock_mode_verify_changed_calls());
    TEST_ASSERT_EQUAL(current_mode, actual_mode);
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
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_BREAK);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_MANUAL, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_DETECTED, LINEBOT_COMMAND_BREAK);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_FOLLOWING, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_NONE);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_LEFT);
    RUN_PARAM_TEST(should_keep_mode, LINEBOT_MODE_RECOVERING, LINEBOT_COMMAND_RIGHT);
    
    return UNITY_END();
}