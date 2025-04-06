#include "core_fixtures.h"
#include <core/vehicle.h>
#include <core_port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

static core_vehicle_t vehicle;

void
setUp(void)
{
    vehicle = VEHICLE;

    core_port_mock_motion_init();
}

void
tearDown(void)
{
}

void
should_apply_following_motion(core_mode_t mode, int expected_apply_count)
{
    // given
    core_vehicle_set_mode(&vehicle, mode);

    // when
    core_vehicle_apply_following_motion(&vehicle, COORDS_ON_ROUTE);

    // then
    TEST_ASSERT_EQUAL(expected_apply_count,
                      core_port_mock_motion_verify_apply_calls());
}

void
should_finish_tracking(void)
{
    // given
    core_vehicle_set_mode(&vehicle, MODE_MANUAL);

    // when
    core_vehicle_apply_following_motion(&vehicle, COORDS_ON_FINISH);

    // then
    core_motion_t expected = MOTION_NONE;
    core_motion_t actual   = core_port_mock_motion_get_applied();

    TEST_ASSERT_TRUE(core_motion_equals(&expected, &actual));
    TEST_ASSERT_EQUAL(1, core_port_mock_motion_verify_applied());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_apply_following_motion, MODE_FOLLOWING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, MODE_RECOVERING, 1);
    RUN_PARAM_TEST(should_apply_following_motion, MODE_DETECTED, 0);
    RUN_PARAM_TEST(should_apply_following_motion, MODE_MANUAL, 0);
    RUN_TEST(should_finish_tracking);
    return UNITY_END();
}