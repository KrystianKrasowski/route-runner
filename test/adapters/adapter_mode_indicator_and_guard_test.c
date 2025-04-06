#include <core/mode.h>
#include <core/ports.h>
#include <tim1_mock.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    tim1_ch1_mock_reset();
}

void
tearDown(void)
{
}

void
should_init_tim1(void)
{
    // when
    core_port_mode_init();

    // then
    TEST_ASSERT_EQUAL(1, tim1_ch1_mock_verify_init_calls());
}

void
should_apply_toggles(core_mode_t mode, uint8_t expected_toggles)
{
    // when
    core_port_mode_changed(&mode);

    // then
    TEST_ASSERT_EQUAL(expected_toggles, tim1_ch1_mock_get_applied_toggles());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_tim1);
    RUN_PARAM_TEST(should_apply_toggles, core_mode(CORE_MODE_MANUAL), 2);
    RUN_PARAM_TEST(should_apply_toggles, core_mode(CORE_MODE_DETECTED), 4);
    RUN_PARAM_TEST(should_apply_toggles, core_mode(CORE_MODE_FOLLOWING), 8);
    RUN_PARAM_TEST(should_apply_toggles, core_mode(CORE_MODE_RECOVERING), 8);
    return UNITY_END();
}