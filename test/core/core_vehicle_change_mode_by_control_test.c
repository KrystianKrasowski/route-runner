#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_mode_indicator.h>
#include <unity.h>
#include <unity_config.h>

static core_vehicle_t vehicle;

void
setUp(void)
{
    vehicle = VEHICLE;
    core_port_mock_mode_indicator_init();
}

void
tearDown(void)
{
}

void
should_change_mode(core_mode_t    current_mode,
                   core_control_t control,
                   core_mode_t    expected_mode)
{
    // given
    core_vehicle_set_mode(&vehicle, current_mode);

    // when
    core_vehicle_change_mode_by_control(&vehicle, control);

    // then
    core_mode_t actual = core_port_mock_mode_indicator_get_applied_mode();
    TEST_ASSERT_TRUE(core_mode_equals(&expected_mode, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_mode_indicator_verify_apply_calls());
}

void
should_keep_mode(core_mode_t mode, core_control_t control)
{
    // given
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_control(&vehicle, control);

    // then
    core_mode_t actual = core_vehicle_get_mode(&vehicle);
    TEST_ASSERT_TRUE(core_mode_equals(&mode, &actual));
    TEST_ASSERT_EQUAL(0, core_port_mock_mode_indicator_verify_apply_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(
        should_change_mode, MODE_DETECTED, CONTROL_FOLLOW, MODE_FOLLOWING);
    RUN_PARAM_TEST(
        should_change_mode, MODE_FOLLOWING, CONTROL_BREAK, MODE_MANUAL);
    RUN_PARAM_TEST(
        should_change_mode, MODE_RECOVERING, CONTROL_BREAK, MODE_MANUAL);

    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_BREAK);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, CONTROL_BREAK);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, CONTROL_FOLLOW);

    return UNITY_END();
}