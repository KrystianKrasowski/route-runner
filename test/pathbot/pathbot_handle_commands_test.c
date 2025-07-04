#include "fixtures.h"
#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <pathbot/port_mock_mode.h>
#include <pathbot/port_mock_motion.h>
#include <pathbot/store.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>

#define CORRECTION_LEFT  -50
#define CORRECTION_RIGHT 50

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
should_update_manual_motion(pathbot_motion_t current_motion,
                            uint16_t         new_commands,
                            pathbot_motion_t expected_motion)
{
    // given
    p_store->mode   = PATHBOT_MODE_MANUAL;
    p_store->motion = current_motion;

    // when
    pathbot_handle_commands(new_commands);

    int motion_changes = pathbot_port_mock_motion_verify_apply_calls();
    int mode_changes   = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_motion_t actual_motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(expected_motion.correction, actual_motion.correction);
    TEST_ASSERT_EQUAL(expected_motion.direction, actual_motion.direction);
    TEST_ASSERT_EQUAL(1, motion_changes);
    TEST_ASSERT_EQUAL(0, mode_changes);
}

void
should_keep_current_motion(pathbot_mode_t   current_mode,
                           pathbot_motion_t current_motion,
                           uint16_t         new_commands)
{
    // given
    p_store->mode   = current_mode;
    p_store->motion = current_motion;

    // when
    pathbot_handle_commands(new_commands);

    int motion_changes = pathbot_port_mock_motion_verify_apply_calls();
    int mode_changes   = pathbot_port_mock_mode_verify_changed_calls();

    // then
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
    p_store->mode = current_mode;

    // when
    pathbot_handle_commands(new_commands);

    int            change_calls = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_mode_t actual_mode  = pathbot_port_mock_mode_get_changed_mode();

    // then
    TEST_ASSERT_EQUAL(expected_mode, actual_mode);
    TEST_ASSERT_EQUAL(1, change_calls);
}

int
main(void)
{
    UNITY_BEGIN();

    // ---- should_update_manual_motion ----

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_backward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_NONE,
                   FIXTURES_MOTION_NONE);

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD,
                   fixtures_motion_forward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_forward(CORRECTION_LEFT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT,
                   fixtures_motion_forward(CORRECTION_RIGHT));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD,
                   fixtures_motion_backward(0));

    RUN_PARAM_TEST(should_update_manual_motion,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT,
                   fixtures_motion_backward(CORRECTION_LEFT));

    // ---- should_keep_manual_motion

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_MOTION_NONE,
                   PATHBOT_COMMAND_LEFT | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(0),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_forward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(0),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(CORRECTION_LEFT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_FOLLOW);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_motion_backward(CORRECTION_RIGHT),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT |
                       PATHBOT_COMMAND_BREAK);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_FORWARD);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_FORWARD | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_BACKWARD);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_LEFT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_BACKWARD | PATHBOT_COMMAND_RIGHT);

    RUN_PARAM_TEST(should_keep_current_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_motion_forward(32),
                   PATHBOT_COMMAND_FOLLOW);

    // ---- should_update_manual_mode

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    return UNITY_END();
}
