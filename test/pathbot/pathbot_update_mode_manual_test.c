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
should_update_manual_mode(pathbot_mode_t current_mode,
                          uint16_t       commands,
                          pathbot_mode_t expected)
{
    // when
    pathbot_mode_t actual = pathbot_update_mode_manual(current_mode, commands);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main()
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    return UNITY_END();
}
