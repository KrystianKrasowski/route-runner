#include <core.h>
#include <core_port_mock.h>
#include <queue.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    core_port_mock_reset();
}

void
should_not_update_motion_on_same_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_vehicle_update_motion(&vehicle);

    // when
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_task_motion_update(&vehicle);

    // then
    TEST_ASSERT_FALSE(core_port_mock_verify_motion_applied());
}

void
should_update_motion_on_different_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_NONE);
    core_vehicle_update_motion(&vehicle);

    // when
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_task_motion_update(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_port_mock_verify_motion_applied());
}

void
should_update_motion(uint16_t                command,
                     core_motion_direction_t expected_direction,
                     int8_t                  expected_angle)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, command);

    // when
    core_task_motion_update(&vehicle);

    // then
    core_motion_t applied_motion = core_port_mock_get_motion_applied();
    TEST_ASSERT_EQUAL(expected_direction, applied_motion.direction);
    TEST_ASSERT_EQUAL(expected_angle, applied_motion.angle);
}

void
should_update_to_stop(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FORWARD);
    core_task_motion_update(&vehicle);

    // when
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_NONE);
    core_task_motion_update(&vehicle);

    // then
    core_motion_t applied_motion = core_port_mock_get_motion_applied();
    TEST_ASSERT_EQUAL(CORE_MOTION_NONE, applied_motion.direction);
    TEST_ASSERT_EQUAL(0, applied_motion.angle);
}

int
main()
{
    UNITY_BEGIN();
    RUN_TEST(should_not_update_motion_on_same_command);
    RUN_TEST(should_update_motion_on_different_command);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_MOTION_FORWARD,
                   0);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_BACKWARD,
                   CORE_MOTION_BACKWARD,
                   0);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_RIGHT,
                   CORE_MOTION_FORWARD,
                   90);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT,
                   CORE_MOTION_FORWARD,
                   -90);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_RIGHT,
                   CORE_MOTION_BACKWARD,
                   90);

    RUN_PARAM_TEST(should_update_motion,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT,
                   CORE_MOTION_BACKWARD,
                   -90);

    RUN_PARAM_TEST(
        should_update_motion, CORE_REMOTE_CONTROL_LEFT, CORE_MOTION_NONE, 0);

    RUN_PARAM_TEST(
        should_update_motion, CORE_REMOTE_CONTROL_RIGHT, CORE_MOTION_NONE, 0);

    RUN_TEST(should_update_to_stop);

    return UNITY_END();
}