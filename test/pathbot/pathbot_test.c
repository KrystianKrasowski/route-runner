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

void
should_update_tracking_mode(pathbot_mode_t   current_mode,
                            pathbot_coords_t coords,
                            pathbot_mode_t   expected)
{
    // when
    pathbot_mode_t actual = pathbot_update_mode_tracking(current_mode, &coords);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
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

void
should_create_pid_motion(pathbot_mode_t      mode,
                         pathbot_coords_t    coords,
                         float               kp,
                         float               ki,
                         float               kd,
                         stack_t             errors,
                         pathbot_direction_t expected_direction,
                         int8_t              expected_correction)
{
    // given
    pathbot_pid_conf_t pid = {
        .kp       = kp,
        .ki       = ki,
        .kd       = kd,
        .p_errors = &errors,
    };

    // when
    pathbot_motion_t motion = pathbot_create_motion_pid(mode, &coords, &pid);

    // then
    TEST_ASSERT_EQUAL(expected_direction, motion.direction);
    TEST_ASSERT_EQUAL(expected_correction, motion.correction);
}

int
main(void)
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

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

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

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_MANUAL,
                   fixtures_coords6_of(0, 0, 100, 100, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, 0),
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_DETECTED,
                   fixtures_coords6_of(0, 0, 100, 100, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, 0),
                   PATHBOT_DIRECTION_NONE,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_coords6_of(0, 0, 100, 100, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, 0),
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_coords6_of(0, 10, 100, 90, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, 0),
                   PATHBOT_DIRECTION_FORWARD,
                   -11);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_coords6_of(0, 20, 100, 80, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, -7),
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_FOLLOWING,
                   fixtures_coords6_of(0, 30, 100, 70, 0, 0),
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, -7, -5),
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_FINISH,
                   0.6,
                   0,
                   3.2,
                   stack_of(5, 0, 0, 0, 0, 0),
                   PATHBOT_DIRECTION_NONE,
                   0);

    return UNITY_END();
}
