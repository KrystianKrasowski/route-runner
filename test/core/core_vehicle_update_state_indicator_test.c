#include <core/vehicle.h>
#include <core_port_mock.h>
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
should_update_state_indicator(core_mode_value_t mode1,
                              core_mode_value_t mode2,
                              int               expected_updates_count)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, mode1);
    core_vehicle_set_mode_value(&vehicle, mode2);

    // when
    core_vehicle_update_state_indicator(&vehicle);

    // then
    int actual_count = core_port_mock_verify_state_indicator_apply_calls();
    TEST_ASSERT_EQUAL(expected_updates_count, actual_count);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_MANUAL,
                   CORE_MODE_LINE_DETECTED,
                   1);
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_MANUAL,
                   CORE_MODE_MANUAL,
                   0);
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_LINE_DETECTED,
                   CORE_MODE_LINE_DETECTED,
                   0);
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_LINE_DETECTED,
                   CORE_MODE_LINE_FOLLOWING,
                   1);
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_MODE_LINE_FOLLOWING,
                   0);
    RUN_PARAM_TEST(should_update_state_indicator,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_MODE_MANUAL,
                   1);
    return UNITY_END();
}