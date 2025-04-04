#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    core_port_mock_motion_init();
}

void
tearDown(void)
{
}

void
should_apply_manual_motion(core_control_t control, core_motion_t expected)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_apply_manual_motion(&vehicle, control);

    // then
    core_motion_t actual = core_port_mock_motion_get_applied();

    TEST_ASSERT_TRUE(core_motion_equals(&actual, &expected));
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());
}

void
should_not_apply_manual_motion_while_following(core_control_t control)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, MODE_LINE_FOLLOWING);

    // when
    core_vehicle_apply_manual_motion(&vehicle, control);

    // then
    TEST_ASSERT_EQUAL(0, core_port_mock_motion_verify_apply_calls());
}

void
should_apply_manual_motion_on_following_break(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, MODE_LINE_FOLLOWING);

    // when
    core_control_t control = CONTROL_BREAK;
    core_vehicle_apply_manual_motion(&vehicle, control);

    // then
    core_motion_t actual   = core_port_mock_motion_get_applied();
    core_motion_t expected = MOTION_NONE;

    TEST_ASSERT_TRUE(core_motion_equals(&actual, &expected));
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_FORWARD,
                   core_motion(CORE_MOTION_FORWARD, 0));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_FORWARD_LEFT,
                   core_motion(CORE_MOTION_FORWARD, -50));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_FORWARD_RIGHT,
                   core_motion(CORE_MOTION_FORWARD, 50));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_BACKWARD,
                   core_motion(CORE_MOTION_BACKWARD, 0));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_BACKWARD_LEFT,
                   core_motion(CORE_MOTION_BACKWARD, -50));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_BACKWARD_RIGHT,
                   core_motion(CORE_MOTION_BACKWARD, 50));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   core_control(CORE_CONTROL_BACKWARD | CORE_CONTROL_FORWARD),
                   core_motion(CORE_MOTION_NONE, 0));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   core_control(CORE_CONTROL_LEFT | CORE_CONTROL_RIGHT),
                   core_motion(CORE_MOTION_NONE, 0));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_FOLLOW,
                   core_motion(CORE_MOTION_NONE, 0));
    RUN_PARAM_TEST(should_apply_manual_motion,
                   CONTROL_BREAK,
                   core_motion(CORE_MOTION_NONE, 0));

    RUN_PARAM_TEST(should_not_apply_manual_motion_while_following,
                   CONTROL_FORWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_following,
                   CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_following,
                   CONTROL_LEFT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_following,
                   CONTROL_RIGHT);
    RUN_PARAM_TEST(should_not_apply_manual_motion_while_following,
                   CONTROL_FOLLOW);

    RUN_TEST(should_apply_manual_motion_on_following_break);

    return UNITY_END();
}