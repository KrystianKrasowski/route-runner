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
should_init_vehicle_mode(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    core_mode_value_t value = core_vehicle_get_mode_value(&vehicle);
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, value);
}

void
should_detect_mode_change_on_init(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_detect_mode_change_on_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_DETECTED);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_detect_mode_change_without_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_DETECTED);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_DETECTED);

    // then
    TEST_ASSERT_FALSE(core_vehicle_is_mode_changed(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_vehicle_mode);
    RUN_TEST(should_detect_mode_change_on_init);
    RUN_TEST(should_detect_mode_change_on_transition);
    RUN_TEST(should_detect_mode_change_without_transition);
    return UNITY_END();
}