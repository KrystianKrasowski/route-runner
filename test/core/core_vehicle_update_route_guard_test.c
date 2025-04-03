#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_route_guard.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    core_port_mock_route_guard_init();
}

void
tearDown(void)
{
}

void
should_start_route_guard_on_following_mode_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_route_guard_verify_start_calls());
}

void
should_not_start_over_route_guard(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, COORDS_ON_ROUTE);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(0, core_port_mock_route_guard_verify_start_calls());
}

void
should_reset_route_guard_while_following_on_route(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, COORDS_ON_ROUTE);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_route_guard_verify_reset_calls());
}

void
should_not_reset_route_guard_while_drifting_off_route(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, COORDS_OFF_ROUTE);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(0, core_port_mock_route_guard_verify_reset_calls());
}

void
should_stop_route_guard_on_manual_mode_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(1, core_port_mock_route_guard_verify_stop_calls());
}

void
should_not_stop_over_route_guard(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_route_guard(&vehicle);

    // then
    TEST_ASSERT_EQUAL(0, core_port_mock_route_guard_verify_stop_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_start_route_guard_on_following_mode_transition);
    RUN_TEST(should_not_start_over_route_guard);
    RUN_TEST(should_reset_route_guard_while_following_on_route);
    RUN_TEST(should_not_reset_route_guard_while_drifting_off_route);
    RUN_TEST(should_stop_route_guard_on_manual_mode_transition);
    RUN_TEST(should_not_stop_over_route_guard);
    return UNITY_END();
}