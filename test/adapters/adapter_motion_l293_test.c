#include <core.h>
#include <gpio_mock.h>
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
should_apply_duty_cycle(int8_t  correction,
                        uint8_t expected_left_duty_cycle,
                        uint8_t expected_right_duty_cycle)
{
    // given
    core_port_motion_init();

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_motion_direction(&vehicle, CORE_MOTION_FORWARD);
    core_vehicle_set_motion_correction(&vehicle, correction);

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
    RUN_PARAM_TEST(should_apply_duty_cycle, -100, 100, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -90, 80, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -80, 60, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -70, 40, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -60, 20, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -50, 0, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -40, 36, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -30, 64, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -20, 84, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -10, 96, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, 0, 100, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, 10, 100, 96);
    RUN_PARAM_TEST(should_apply_duty_cycle, 20, 100, 84);
    RUN_PARAM_TEST(should_apply_duty_cycle, 30, 100, 64);
    RUN_PARAM_TEST(should_apply_duty_cycle, 40, 100, 36);
    RUN_PARAM_TEST(should_apply_duty_cycle, 50, 100, 0);
    RUN_PARAM_TEST(should_apply_duty_cycle, 60, 100, 20);
    RUN_PARAM_TEST(should_apply_duty_cycle, 70, 100, 40);
    RUN_PARAM_TEST(should_apply_duty_cycle, 80, 100, 60);
    RUN_PARAM_TEST(should_apply_duty_cycle, 90, 100, 80);
    RUN_PARAM_TEST(should_apply_duty_cycle, 100, 100, 100);
    return UNITY_END();
}