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
should_create_manual_motion(core_motion_direction_t direction,
                            int8_t                  correction,
                            uint16_t                commands)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_control(&vehicle, core_control(commands));
    core_vehicle_update_motion(&vehicle);
    core_motion_t motion = core_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(direction, core_motion_get_direction(&motion));
    TEST_ASSERT_EQUAL(correction, core_motion_get_correction(&motion));
}

void
should_remain_manual_motion_for_same_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_control_t control = core_control(CORE_CONTROL_FORWARD);

    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_control(&vehicle, control);
    core_vehicle_update_motion(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());

    // when
    core_vehicle_update_control(&vehicle, control);
    core_vehicle_update_motion(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());
}

void
should_create_tracking_motion_going_forward(void)
{
    // given
    core_vehicle_t vehicle;

    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle,
                               core_coords(0, 0, 100, 100, 0, 0));

    // when
    core_vehicle_update_motion(&vehicle);
    core_motion_t motion = core_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(CORE_MOTION_FORWARD, core_motion_get_direction(&motion));
    TEST_ASSERT_EQUAL(0, core_motion_get_correction(&motion));
}

void
should_create_tracking_motion_turning_left(core_coords_t coords)
{
    // given
    core_vehicle_t vehicle;

    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_motion(&vehicle);
    core_motion_t motion = core_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(CORE_MOTION_FORWARD, core_motion_get_direction(&motion));
    TEST_ASSERT_LESS_THAN(0, core_motion_get_correction(&motion));
}

void
should_create_tracking_motion_turning_right(core_coords_t coords)
{
    // given
    core_vehicle_t vehicle;

    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_motion(&vehicle);
    core_motion_t motion = core_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(CORE_MOTION_FORWARD, core_motion_get_direction(&motion));
    TEST_ASSERT_GREATER_THAN(0, core_motion_get_correction(&motion));
}

void
should_remain_tracking_motion_without_coords_update(void)
{
    // given
    core_vehicle_t        vehicle;

    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle,
                               core_coords(0, 0, 90, 100, 0, 0));

    // when
    core_vehicle_update_motion(&vehicle);
    core_vehicle_update_motion(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_FORWARD,
                   0,
                   CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_FORWARD,
                   -50,
                   CORE_CONTROL_FORWARD | CORE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_FORWARD,
                   50,
                   CORE_CONTROL_FORWARD | CORE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_BACKWARD,
                   0,
                   CORE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_BACKWARD,
                   -50,
                   CORE_CONTROL_BACKWARD | CORE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_create_manual_motion,
                   CORE_MOTION_BACKWARD,
                   50,
                   CORE_CONTROL_BACKWARD | CORE_CONTROL_RIGHT);

    RUN_TEST(should_remain_manual_motion_for_same_command);

    RUN_TEST(should_create_tracking_motion_going_forward);

    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(0, 20, 100, 80, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(0, 40, 100, 60, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(0, 60, 100, 40, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(0, 80, 100, 20, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(0, 100, 100, 0, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(20, 100, 80, 0, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(40, 100, 60, 0, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(60, 100, 40, 0, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(80, 100, 20, 0, 0, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_left,
                   core_coords(100, 100, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 80, 100, 20, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 60, 100, 40, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 40, 100, 60, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 20, 100, 80, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 100, 100, 0));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 80, 100, 20));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 60, 100, 40));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 40, 100, 60));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 20, 100, 80));
    RUN_PARAM_TEST(should_create_tracking_motion_turning_right,
                   core_coords(0, 0, 0, 0, 100, 100));

    RUN_TEST(should_remain_tracking_motion_without_coords_update);

    return UNITY_END();
}