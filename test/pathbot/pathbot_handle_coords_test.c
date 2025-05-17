#include "fixtures.h"
#include "pathbot/domain.h"
#include <pathbot/api.h>
#include <pathbot/port_mock_mode.h>
#include <pathbot/port_mock_motion.h>
#include <pathbot/store.h>
#include <unity.h>
#include <unity_config.h>

static pathbot_store_t *p_store;

void
setUp(void)
{
    pathbot_store_init(NULL);
    p_store = pathbot_store_get();
}

void
tearDown(void)
{
    pathbot_port_mock_mode_reset();
    pathbot_port_mock_motion_reset();
}

void
should_update_mode(pathbot_mode_t   current_mode,
                   pathbot_coords_t new_coords,
                   pathbot_mode_t   expexted_mode)
{
    // given
    p_store->mode = current_mode;

    // when
    pathbot_handle_coords(&new_coords);

    int            change_calls = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_mode_t actual_mode  = pathbot_port_mock_mode_get_changed_mode();

    // then
    TEST_ASSERT_EQUAL(expexted_mode, actual_mode);
    TEST_ASSERT_EQUAL(1, change_calls);
}

void
should_be_turning_left(pathbot_coords_t coords)
{
    // given
    p_store->mode   = PATHBOT_MODE_FOLLOWING;
    p_store->motion = fixtures_motion_forward(0);

    // when
    pathbot_handle_coords(&coords);

    int apply_calls         = pathbot_port_mock_motion_verify_apply_calls();
    pathbot_motion_t motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_FORWARD, motion.direction);
    TEST_ASSERT_LESS_THAN(0, motion.correction);
    TEST_ASSERT_EQUAL(1, apply_calls);
}

void
should_be_turning_right(pathbot_coords_t coords)
{
    // given
    p_store->mode   = PATHBOT_MODE_FOLLOWING;
    p_store->motion = fixtures_motion_forward(0);

    // when
    pathbot_handle_coords(&coords);

    int apply_calls         = pathbot_port_mock_motion_verify_apply_calls();
    pathbot_motion_t motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_FORWARD, motion.direction);
    TEST_ASSERT_GREATER_THAN(0, motion.correction);
    TEST_ASSERT_EQUAL(1, apply_calls);
}

void
should_stop_on_finish(void)
{
    // given
    p_store->mode   = PATHBOT_MODE_FOLLOWING;
    p_store->motion = fixtures_motion_forward(0);

    // when
    pathbot_coords_t coords = FIXTURES_COORDS6_ON_FINISH;
    pathbot_handle_coords(&coords);

    int apply_calls         = pathbot_port_mock_motion_verify_apply_calls();
    pathbot_motion_t motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_NONE, motion.direction);
    TEST_ASSERT_EQUAL(0, motion.correction);
    TEST_ASSERT_EQUAL(1, apply_calls);
}

int
main(void)
{
    UNITY_BEGIN();

    // ---- should_update_mode

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    // ---- should_be_turning_left

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(0, 20, 100, 80, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(0, 40, 100, 60, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(0, 60, 100, 40, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(0, 80, 100, 20, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(0, 100, 100, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(20, 100, 80, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(40, 100, 60, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(60, 100, 40, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(80, 100, 20, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 100, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 80, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 60, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 40, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 20, 0, 0, 0, 0));

    RUN_PARAM_TEST(should_be_turning_left,
                   fixtures_coords6_of(100, 0, 0, 0, 0, 0));

    // ---- should_be_turning_right

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 80, 100, 20, 0));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 60, 100, 40, 0));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 40, 100, 60, 0));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 20, 100, 80, 0));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 100, 100, 0));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 80, 100, 20));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 60, 100, 40));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 40, 100, 60));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 20, 100, 80));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 100, 100));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 80, 100));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 60, 100));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 40, 100));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 20, 100));

    RUN_PARAM_TEST(should_be_turning_right,
                   fixtures_coords6_of(0, 0, 0, 0, 0, 100));

    RUN_TEST(should_stop_on_finish);

    return UNITY_END();
}
