#include <core.h>
#include <core_port_mock.h>
#include <unity.h>

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
should_update_state_indicator_after_initialization(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_task_state_indicator_update(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_port_mock_verify_state_indicator_updated());
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_port_mock_get_state_indicator_applied());
}

void
should_update_state_indicator_on_state_change(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_MANUAL);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_task_state_indicator_update(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_port_mock_verify_state_indicator_updated());
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_DETECTED,
                      core_port_mock_get_state_indicator_applied());
}

void
should_not_update_state_indicator_without_change(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_task_state_indicator_update(&vehicle);

    // then
    TEST_ASSERT_FALSE(core_port_mock_verify_state_indicator_updated());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_update_state_indicator_after_initialization);
    RUN_TEST(should_update_state_indicator_on_state_change);
    RUN_TEST(should_not_update_state_indicator_without_change);
    return UNITY_END();
}