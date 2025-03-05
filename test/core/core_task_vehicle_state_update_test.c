#include <core.h>
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
should_stay_manual(void)
{
    // given
    core_position_t position = {10, 10, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_task_vehicle_state_update(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

void
should_transit_to_line_detected_from_manual(void)
{
    // given
    core_position_t position = {10, 110, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_task_vehicle_state_update(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_DETECTED,
                      core_vehicle_get_state(&vehicle));
}

void
should_stay_line_detected(void)
{
    // given
    core_position_t position = {10, 110, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_task_vehicle_state_update(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_DETECTED,
                      core_vehicle_get_state(&vehicle));

    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

void
should_transit_to_manual_from_line_detected(void)
{
    // given
    core_position_t position = {10, 10, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_task_vehicle_state_update(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_stay_manual);
    RUN_TEST(should_transit_to_line_detected_from_manual);
    RUN_TEST(should_stay_line_detected);
    RUN_TEST(should_transit_to_manual_from_line_detected);
    return UNITY_END();
}