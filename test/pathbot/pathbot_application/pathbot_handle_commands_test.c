#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <pathbot/fixtures.h>
#include <pathbot/port_mock_mode.h>
#include <pathbot/port_mock_motion.h>
#include <pathbot/store.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>

static pathbot_store_t *p_store;

void
setUp(void)
{
    p_store = pathbot_store_get();
}

void
tearDown(void)
{
    pathbot_port_mock_motion_reset();
    pathbot_port_mock_mode_reset();
}

void
should_update_manual_motion(uint16_t         current_commands,
                            pathbot_motion_t current_motion,
                            uint16_t         new_commands,
                            pathbot_motion_t expected_motion)
{
    // given
    p_store->mode     = PATHBOT_MODE_MANUAL;
    p_store->commands = current_commands;
    p_store->motion   = current_motion;

    // when
    int result         = pathbot_handle_commands(new_commands);
    int motion_changes = pathbot_port_mock_motion_verify_apply_calls();
    int mode_changes   = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_motion_t actual_motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(expected_motion.correction, actual_motion.correction);
    TEST_ASSERT_EQUAL(expected_motion.direction, actual_motion.direction);
    TEST_ASSERT_EQUAL(1, motion_changes);
    TEST_ASSERT_EQUAL(0, mode_changes);
}

void
should_keep_manual_motion(uint16_t         current_commands,
                          pathbot_motion_t current_motion,
                          uint16_t         new_commands)
{
    // given
    p_store->mode     = PATHBOT_MODE_MANUAL;
    p_store->commands = current_commands;
    p_store->motion   = current_motion;

    // when
    int result         = pathbot_handle_commands(new_commands);
    int motion_changes = pathbot_port_mock_motion_verify_apply_calls();
    int mode_changes   = pathbot_port_mock_mode_verify_changed_calls();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(p_store->motion.correction, current_motion.correction);
    TEST_ASSERT_EQUAL(p_store->motion.direction, current_motion.direction);
    TEST_ASSERT_EQUAL(0, motion_changes);
    TEST_ASSERT_EQUAL(0, mode_changes);
}

void
should_update_mode(pathbot_mode_t current_mode,
                   uint16_t       new_commands,
                   pathbot_mode_t expected_mode)
{
    // given
    p_store->mode     = current_mode;
    p_store->commands = PATHBOT_COMMAND_NONE;

    // when
    int            result       = pathbot_handle_commands(new_commands);
    int            change_calls = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_mode_t actual_mode  = pathbot_port_mock_mode_get_changed_mode();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(expected_mode, actual_mode);
    TEST_ASSERT_EQUAL(1, change_calls);
}

void
should_noop_on_same_commands(uint16_t current_commands, uint16_t new_commands)
{
    // given
    p_store->commands = current_commands;

    // when
    int result         = pathbot_handle_commands(new_commands);
    int mode_changes   = pathbot_port_mock_mode_verify_changed_calls();
    int motion_changes = pathbot_port_mock_motion_verify_apply_calls();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_NOOP, result);
    TEST_ASSERT_EQUAL(0, mode_changes);
    TEST_ASSERT_EQUAL(0, motion_changes);
}

int
main(void)
{
    UNITY_BEGIN();

    // ---- should_update_manual_motion ----

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50));

    // ---- should_keep_manual_motion

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_BREAK);

    // ---- should_update_manual_mode

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    // ---- should_noop_on_same_commands

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_COMMAND_NONE);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_COMMAND_FORWARD);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_COMMAND_BACKWARD);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_noop_on_same_commands,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT);

    return UNITY_END();
}
