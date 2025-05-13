#include "fixtures.h"
#include <pathbot/domain.h>
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
                          pathbot_mode_t expected_mode,
                          bool           b_expected_changed)
{
    // given
    pathbot_mode_t mode = current_mode;

    // when
    bool b_changed = pathbot_update_mode_manual(commands, &mode);

    // then
    TEST_ASSERT_EQUAL(expected_mode, mode);
    TEST_ASSERT_EQUAL(b_expected_changed, b_changed);
}

int
main()
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_RECOVERING,
                   false);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING,
                   true);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL,
                   true);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL,
                   true);

    return UNITY_END();
}
