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
should_create_manual_motion(core_motion_direction_t direction,
                            int8_t                  correction,
                            uint16_t                commands)
{
    // given
    core_motion_t motion;
    core_motion_init(&motion);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_control(&vehicle, core_control_create(commands));
    core_vehicle_result_t result =
        core_vehicle_create_motion(&vehicle, &motion);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_MOTION_CHANGED, result);
    TEST_ASSERT_EQUAL(direction, core_motion_get_direction(&motion));
    TEST_ASSERT_EQUAL(correction, core_motion_get_correction(&motion));
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
    return UNITY_END();
}