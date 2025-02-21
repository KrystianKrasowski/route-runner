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
should_apply_duty_cycle_based_on_motion_angle(int8_t  angle,
                                              uint8_t expected_left_duty_cycle,
                                              uint8_t expected_right_duty_cycle)
{
    // given
    core_port_motion_init();

    // when
    core_motion_t motion = {CORE_MOTION_BACKWARD, angle};
    core_port_motion_apply(&motion);

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
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 0, 96, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -90, 20, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 90, 96, 20);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -30, 71, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 30, 96, 71);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -45, 58, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 45, 96, 58);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, -60, 46, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle_based_on_motion_angle, 60, 96, 46);
    return UNITY_END();
}