#include <pathbot/domain.h>
#include <pathbot/fixtures.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_update_manual_motion(pathbot_motion_t motion,
                            uint16_t         commands,
                            pathbot_motion_t expected_motion,
                            bool             b_expected_changed)
{
    // when
    bool b_changed = pathbot_update_motion_manual(commands, &motion);

    // then
    TEST_ASSERT_EQUAL(b_expected_changed, b_changed);
    TEST_ASSERT_EQUAL(expected_motion.direction, motion.direction);
    TEST_ASSERT_EQUAL(expected_motion.correction, motion.correction);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BACKWARD,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT | PATHBOT_COMMAND_RIGHT,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_RIGHT,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FOLLOW,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BREAK,
                   FIXTURES_MOTION_NONE,
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(-50),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(50),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(-50),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(50),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(-50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(-50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(50),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE,
                   true);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_FOLLOW,
                   fixtures_motion_forward(0),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_FOLLOW,
                   fixtures_motion_backward(0),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BREAK,
                   fixtures_motion_forward(0),
                   false);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_BREAK,
                   fixtures_motion_backward(0),
                   false);

    return UNITY_END();
}
