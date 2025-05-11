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
should_stand_on_null_past_errors(void)
{
    // given
    pathbot_pid_conf_t pid = {
        .kp = 0.6,
        .ki = 0,
        .kd = 3.2,
    };

    // when
    pathbot_motion_t motion = pathbot_create_motion_pid(23, NULL, &pid);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_NONE, motion.direction);
    TEST_ASSERT_EQUAL(0, motion.correction);
}

void
should_stand_on_null_pid_config(void)
{
    // given
    stack_t past_errors = stack_of(5, 0, 0, 0, 0, 0);

    // when
    pathbot_motion_t motion = pathbot_create_motion_pid(23, &past_errors, NULL);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_NONE, motion.direction);
    TEST_ASSERT_EQUAL(0, motion.correction);
}

void
should_create_pid_motion(int                 error,
                         stack_t             past_errors,
                         float               kp,
                         float               ki,
                         float               kd,
                         pathbot_direction_t expected_direction,
                         int8_t              expected_correction)
{
    // given
    pathbot_pid_conf_t pid = {
        .kp = kp,
        .ki = ki,
        .kd = kd,
    };

    // when
    pathbot_motion_t motion =
        pathbot_create_motion_pid(error, &past_errors, &pid);

    // then
    TEST_ASSERT_EQUAL(expected_direction, motion.direction);
    TEST_ASSERT_EQUAL(expected_correction, motion.correction);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_stand_on_null_past_errors);
    RUN_TEST(should_stand_on_null_pid_config);

    RUN_PARAM_TEST(should_create_pid_motion,
                   0,
                   stack_of(5, 0, 0, 0, 0, 0),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -3,
                   stack_of(5, 0, 0, 0, 0, 0),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -11);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -6,
                   stack_of(5, 0, 0, 0, 0, -3),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -13);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -9,
                   stack_of(5, 0, 0, 0, -3, -6),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -15);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -12,
                   stack_of(5, 0, 0, -3, -6, -9),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -16);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -15,
                   stack_of(5, 0, -3, -6, -9, -12),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -18);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -30,
                   stack_of(5, -3, -6, -9, -12, -15),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -66);

    RUN_PARAM_TEST(should_create_pid_motion,
                   -50,
                   stack_of(5, -6, -9, -12, -15, -30),
                   0.6,
                   0,
                   3.2,
                   PATHBOT_DIRECTION_FORWARD,
                   -94);

    return UNITY_END();
}
