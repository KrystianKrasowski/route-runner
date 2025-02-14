#include <core.h>
#include <unity.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_init_vehicle_state(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    core_vehicle_state_t state = core_vehicle_get_state(&vehicle);
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL, state);
}

void
should_detect_state_change_on_init(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_state_changed(&vehicle));
}

void
should_detect_state_change_on_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_MANUAL);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_state_changed(&vehicle));
}

void
should_detect_state_change_without_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);

    // then
    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_vehicle_state);
    RUN_TEST(should_detect_state_change_on_init);
    RUN_TEST(should_detect_state_change_on_transition);
    RUN_TEST(should_detect_state_change_without_transition);
    return UNITY_END();
}