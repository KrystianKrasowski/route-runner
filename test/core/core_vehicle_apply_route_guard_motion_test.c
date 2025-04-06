#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_mode.h>
#include <core_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static core_vehicle_t vehicle;

void
setUp(void)
{
    vehicle = VEHICLE;
    core_port_mock_motion_init();
    core_port_mock_mode_init();
}

void
tearDown(void)
{
}

void
should_reset_to_manual_mode(void)
{
    // when
    core_vehicle_timeout_route_guard(&vehicle);

    // then
    core_mode_t actual   = core_vehicle_get_mode(&vehicle);
    core_mode_t expected = MODE_MANUAL;
    TEST_ASSERT_TRUE(core_mode_equals(&expected, &actual));
}

void
should_apply_stop_motion(void)
{
    // when
    core_vehicle_timeout_route_guard(&vehicle);

    // then
    core_motion_t actual   = core_port_mock_motion_get_applied();
    core_motion_t expected = MOTION_NONE;
    TEST_ASSERT_TRUE(core_motion_equals(&expected, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_apply_calls());
}

void
should_reset_state_indicator(void)
{
    // when
    core_vehicle_timeout_route_guard(&vehicle);

    // then
    core_mode_t actual   = core_port_mock_mode_get_changed_mode();
    core_mode_t expected = MODE_MANUAL;
    TEST_ASSERT_TRUE(core_mode_equals(&expected, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_mode_verify_changed_calls());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_reset_to_manual_mode);
    RUN_TEST(should_apply_stop_motion);
    RUN_TEST(should_reset_state_indicator);
    return UNITY_END();
}