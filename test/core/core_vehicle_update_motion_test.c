#include <core/types.h>
#include <core/vehicle.h>
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
should_update_motion_while_in_manual_mode(core_motion_direction_t direction,
                                          int8_t                  correction,
                                          uint16_t                command)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_command(&vehicle, command);
    core_vehicle_result_t result = core_vehicle_update_motion(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_MOTION_CHANGED, result);
    TEST_ASSERT_EQUAL(direction, core_vehicle_get_motion_direction(&vehicle));
    TEST_ASSERT_EQUAL(correction, core_vehicle_get_motion_correction(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_FORWARD,
                   0,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_FORWARD,
                   -50,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_FORWARD,
                   50,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_BACKWARD,
                   0,
                   CORE_REMOTE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_BACKWARD,
                   -50,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_mode,
                   CORE_MOTION_BACKWARD,
                   50,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_RIGHT);
    return UNITY_END();
}