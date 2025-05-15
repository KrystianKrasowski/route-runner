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
                            int              expected_apply_calls)
{
    // given
    p_store->mode     = PATHBOT_MODE_MANUAL;
    p_store->commands = current_commands;
    p_store->motion   = current_motion;

    // when
    int result = pathbot_handle_commands(new_commands);

    // then
    int apply_calls = pathbot_port_mock_motion_verify_apply_calls();

    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(new_commands, p_store->commands);
    TEST_ASSERT_EQUAL(expected_apply_calls, apply_calls);
}

void
should_noop_on_same_commands(uint16_t current_commands, uint16_t new_commands)
{
    // given
    p_store->commands = current_commands;

    // when
    int result = pathbot_handle_commands(new_commands);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_NOOP, result);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_NONE,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   1);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_FOLLOW,
                   0);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_FOLLOW,
                   0);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BREAK,
                   0);

    RUN_PARAM_TEST(should_update_manual_motion,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_BREAK,
                   0);

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
