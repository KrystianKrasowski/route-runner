#include <core.h>
#include <gpio_mock.h>
#include <tim3_mock.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    core_port_motion_init();
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
    core_motion_t motion = core_motion(CORE_MOTION_FORWARD, correction);

    // when
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
    RUN_PARAM_TEST(should_apply_duty_cycle, -100, 100, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -90, 80, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -80, 60, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -70, 40, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -60, 20, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -50, 0, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -40, 20, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -30, 40, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -20, 60, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, -10, 80, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, 0, 100, 100);
    RUN_PARAM_TEST(should_apply_duty_cycle, 10, 100, 80);
    RUN_PARAM_TEST(should_apply_duty_cycle, 20, 100, 60);
    RUN_PARAM_TEST(should_apply_duty_cycle, 30, 100, 40);
    RUN_PARAM_TEST(should_apply_duty_cycle, 40, 100, 20);
    RUN_PARAM_TEST(should_apply_duty_cycle, 50, 100, 0);
    RUN_PARAM_TEST(should_apply_duty_cycle, 60, 100, 20);
    RUN_PARAM_TEST(should_apply_duty_cycle, 70, 100, 40);
    RUN_PARAM_TEST(should_apply_duty_cycle, 80, 100, 60);
    RUN_PARAM_TEST(should_apply_duty_cycle, 90, 100, 80);
    RUN_PARAM_TEST(should_apply_duty_cycle, 100, 100, 100);
    return UNITY_END();
}