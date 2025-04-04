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
should_change_mode(core_mode_t mode, core_coords_t coords, core_mode_t expected)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_coords(&vehicle, coords);

    // then
    core_mode_t actual = core_port_mock_mode_indicator_get_applied_mode();

    TEST_ASSERT_TRUE(core_mode_equals(&expected, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_mode_indicator_verify_apply_calls());
}

void
should_keep_mode(core_mode_t mode, core_coords_t coords)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_coords(&vehicle, coords);

    // then
    core_mode_t actual = core_vehicle_get_mode(&vehicle);

    TEST_ASSERT_TRUE(core_mode_equals(&mode, &actual));
    TEST_ASSERT_EQUAL(0, core_port_mock_mode_indicator_verify_apply_calls());
}

void
should_handle_route_guard(core_mode_t   mode,
                          core_coords_t coords,
                          int           guard_reset)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_coords(&vehicle, coords);

    // then
    TEST_ASSERT_EQUAL(guard_reset,
                      core_port_mock_route_guard_verify_reset_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(
        should_change_mode, MODE_MANUAL, COORDS_ON_ROUTE, MODE_LINE_DETECTED);
    RUN_PARAM_TEST(
        should_change_mode, MODE_LINE_DETECTED, COORDS_OFF_ROUTE, MODE_MANUAL);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, COORDS_OFF_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_DETECTED, COORDS_ON_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, COORDS_ON_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_LINE_FOLLOWING, COORDS_OFF_ROUTE);

    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, COORDS_ON_ROUTE, 1);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_FOLLOWING, COORDS_OFF_ROUTE, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, COORDS_ON_ROUTE, 0);
    RUN_PARAM_TEST(
        should_handle_route_guard, MODE_LINE_DETECTED, COORDS_OFF_ROUTE, 0);
    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, COORDS_ON_ROUTE, 0);
    RUN_PARAM_TEST(should_handle_route_guard, MODE_MANUAL, COORDS_OFF_ROUTE, 0);

    return UNITY_END();
}