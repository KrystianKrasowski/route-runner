#include <core.h>
#include <tim3_mock.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    tim3_mock_reset();
}

void
tearDown(void)
{
}

void
should_apply_duty_cycle_based_on_motion_angle(int8_t  correction,
                                              uint8_t expected_left_duty_cycle,
                                              uint8_t expected_right_duty_cycle)
{
    // given
    core_port_motion_init();

    core_motion_t motion = {CORE_MOTION_BACKWARD, correction};
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    vehicle.motion = motion;

    // when
    core_port_motion_apply(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_left_duty_cycle,
                      tim3_mock_verify_channel3_duty_cycle());

    TEST_ASSERT_EQUAL(expected_right_duty_cycle,
                      tim3_mock_verify_channel4_duty_cycle());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 0, 100, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -90, 10, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 90, 100, 10);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -30, 70, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 30, 100, 70);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -45, 55, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 45, 100, 55);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -60, 40, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 60, 100, 40);
    return UNITY_END();
}