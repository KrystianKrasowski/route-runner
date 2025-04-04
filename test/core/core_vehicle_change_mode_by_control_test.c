#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_mode_indicator.h>
#include <core_port_mock_route_guard.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    core_port_mock_mode_indicator_init();
    core_port_mock_route_guard_init();
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
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
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
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_control(&vehicle, control);

    // then
    core_mode_t actual = core_vehicle_get_mode(&vehicle);
    TEST_ASSERT_TRUE(core_mode_equals(&mode, &actual));
    TEST_ASSERT_EQUAL(0, core_port_mock_mode_indicator_verify_apply_calls());
}

void
should_handle_route_guard(core_mode_t    mode,
                          core_control_t control,
                          int            guard_start,
                          int            guard_stop)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_control(&vehicle, control);

    // then
    TEST_ASSERT_EQUAL(guard_start,
                      core_port_mock_route_guard_verify_start_calls());
    TEST_ASSERT_EQUAL(guard_stop,
                      core_port_mock_route_guard_verify_stop_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_change_mode,
                   MODE_LINE_DETECTED,
                   CONTROL_FOLLOW,
                   MODE_LINE_FOLLOWING);
    RUN_PARAM_TEST(
        should_change_mode, MODE_LINE_FOLLOWING, CONTROL_BREAK, MODE_MANUAL);

    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_BREAK);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, CONTROL_BREAK);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_NONE);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_FORWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_LEFT);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_RIGHT);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, CONTROL_FOLLOW);

    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, CONTROL_NONE, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_FORWARD, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_BACKWARD, 0, 0);
    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, CONTROL_LEFT, 0, 0);
    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, CONTROL_RIGHT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_FORWARD_LEFT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_FORWARD_RIGHT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_BACKWARD_LEFT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_BACKWARD_RIGHT, 0, 0);
    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, CONTROL_BREAK, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_MANUAL, CONTROL_FOLLOW, 0, 0);

    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_NONE, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_FORWARD, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_BACKWARD, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_LEFT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_RIGHT, 0, 0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_DETECTED,
                   CONTROL_FORWARD_LEFT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_DETECTED,
                   CONTROL_FORWARD_RIGHT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_DETECTED,
                   CONTROL_BACKWARD_LEFT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_DETECTED,
                   CONTROL_BACKWARD_RIGHT,
                   0,
                   0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_BREAK, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, CONTROL_FOLLOW, 1, 0);

    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_NONE, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_FORWARD, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_BACKWARD, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_LEFT, 0, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_RIGHT, 0, 0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_FOLLOWING,
                   CONTROL_FORWARD_LEFT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_FOLLOWING,
                   CONTROL_FORWARD_RIGHT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_FOLLOWING,
                   CONTROL_BACKWARD_LEFT,
                   0,
                   0);
    RUN_PARAM_TEST(should_handle_route_guard,
                   MODE_LINE_FOLLOWING,
                   CONTROL_BACKWARD_RIGHT,
                   0,
                   0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_BREAK, 0, 1);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, CONTROL_FOLLOW, 0, 0);

    return UNITY_END();
}