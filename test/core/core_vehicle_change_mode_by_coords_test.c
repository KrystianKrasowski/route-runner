#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_mode.h>
#include <unity.h>
#include <unity_config.h>

static core_vehicle_t vehicle;

void
setUp(void)
{
    vehicle = VEHICLE;
    core_port_mock_mode_init();
}

void
tearDown(void)
{
}

void
should_change_mode(core_mode_t mode, core_coords_t coords, core_mode_t expected)
{
    // given
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_coords(&vehicle, coords);

    // then
    core_mode_t actual = core_port_mock_mode_get_changed_mode();

    TEST_ASSERT_TRUE(core_mode_equals(&expected, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_mode_verify_changed_calls());
}

void
should_keep_mode(core_mode_t mode, core_coords_t coords)
{
    // given
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_change_mode_by_coords(&vehicle, coords);

    // then
    core_mode_t actual = core_vehicle_get_mode(&vehicle);

    TEST_ASSERT_TRUE(core_mode_equals(&mode, &actual));
    TEST_ASSERT_EQUAL(0, core_port_mock_mode_verify_changed_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(
        should_change_mode, MODE_MANUAL, COORDS_ON_ROUTE, MODE_DETECTED);
    RUN_PARAM_TEST(
        should_change_mode, MODE_DETECTED, COORDS_OFF_ROUTE, MODE_MANUAL);
    RUN_PARAM_TEST(
        should_change_mode, MODE_FOLLOWING, COORDS_OFF_ROUTE, MODE_RECOVERING);
    RUN_PARAM_TEST(
        should_change_mode, MODE_RECOVERING, COORDS_ON_ROUTE, MODE_FOLLOWING);
    RUN_PARAM_TEST(
        should_change_mode, MODE_FOLLOWING, COORDS_ON_FINISH, MODE_MANUAL);
    RUN_PARAM_TEST(
        should_change_mode, MODE_RECOVERING, COORDS_ON_FINISH, MODE_MANUAL);
    RUN_PARAM_TEST(should_keep_mode, MODE_MANUAL, COORDS_OFF_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_DETECTED, COORDS_ON_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_FOLLOWING, COORDS_ON_ROUTE);
    RUN_PARAM_TEST(should_keep_mode, MODE_RECOVERING, COORDS_OFF_ROUTE);

    return UNITY_END();
}