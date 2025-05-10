#include "fixtures.h"
#include <pathbot.h>
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
should_create_manual_motion(pathbot_mode_t      current_mode,
                            uint16_t            commands,
                            pathbot_direction_t expected_direction,
                            int8_t              expected_correction)
{
    // when
    pathbot_motion_t motion =
        pathbot_create_motion_manual(current_mode, commands);

    // then
    TEST_ASSERT_EQUAL(expected_direction, motion.direction);
    TEST_ASSERT_EQUAL(expected_correction, motion.correction);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_FORWARD,
                   -50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_FORWARD,
                   50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_BACKWARD,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_BACKWARD,
                   -50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_BACKWARD,
                   50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_LEFT | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_FORWARD,
                   -50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_FORWARD,
                   50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_BACKWARD,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_BACKWARD,
                   -50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_BACKWARD,
                   50);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_LEFT | PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_manual_motion,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_DIRECTION_NONE,
                   0);

    return UNITY_END();
}
