#include "pathbot/domain.h"
#include <pathbot/api.h>
#include <pathbot/port_mock_mode.h>
#include <pathbot/port_mock_motion.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    pathbot_port_mock_mode_reset();
    pathbot_port_mock_motion_reset();
}

void
should_stop_immediatly(void)
{
    // when
    int result              = pathbot_handle_route_guard_timeout();
    int apply_calls         = pathbot_port_mock_motion_verify_apply_calls();
    pathbot_motion_t motion = pathbot_port_mock_motion_get_applied();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(0, motion.correction);
    TEST_ASSERT_EQUAL(PATHBOT_DIRECTION_NONE, motion.direction);
    TEST_ASSERT_EQUAL(1, apply_calls);
}

void
should_update_mode(void)
{
    // when
    int            result      = pathbot_handle_route_guard_timeout();
    int            apply_calls = pathbot_port_mock_mode_verify_changed_calls();
    pathbot_mode_t mode        = pathbot_port_mock_mode_get_changed_mode();

    // then
    TEST_ASSERT_EQUAL(PATHBOT_RESULT_OK, result);
    TEST_ASSERT_EQUAL(PATHBOT_MODE_MANUAL, mode);
    TEST_ASSERT_EQUAL(1, apply_calls);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_stop_immediatly);

    RUN_TEST(should_update_mode);

    return UNITY_END();
}
