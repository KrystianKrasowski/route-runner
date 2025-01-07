#include "core.h"
#include "core_interface_mock.h"
#include "unity.h"
#include "unity_config.h"
#include <stdbool.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    core_mock_reset();
}

void
should_stay_when_turned_on(void)
{
    // when
    core_execute();

    // then
    TEST_ASSERT_VEHICLE_RUNNING(false);
    TEST_ASSERT_VEHICLE_STATE(CORE_VEHICLE_STATE_STANDBY);
}

void
should_stay_on_reset_command(void)
{
    // given
    core_mock_set_line_detected(true);
    core_mock_set_command(CORE_COMMAND_RESET);

    // when
    core_execute();

    // then
    TEST_ASSERT_VEHICLE_RUNNING(false);
    TEST_ASSERT_VEHICLE_STATE(CORE_VEHICLE_STATE_STANDBY);
}

void
should_stay_when_line_just_detected(void)
{
    // given
    core_mock_set_line_detected(true);

    // when
    core_execute();

    // then
    TEST_ASSERT_VEHICLE_RUNNING(false);
    TEST_ASSERT_VEHICLE_STATE(CORE_VEHICLE_STATE_READY);
}

void
should_start_running(void)
{
    // given
    core_mock_set_line_detected(true);
    core_mock_set_command(CORE_COMMAND_RUN);

    // when
    core_execute();

    // then
    TEST_ASSERT_VEHICLE_RUNNING(true);
    TEST_ASSERT_VEHICLE_STATE(CORE_VEHICLE_STATE_RUNNING);
}

void
should_apply_control(core_control_direction_t direction, uint8_t angle)
{
    // given
    core_mock_set_line_detected(true);
    core_mock_set_command(CORE_COMMAND_RUN);
    core_mock_set_control(direction, angle);

    // when
    core_execute();

    // then
    TEST_ASSERT_VEHICLE_DIRECTION(direction);
    TEST_ASSERT_VEHICLE_ANGLE(angle);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_stay_when_turned_on);
    RUN_TEST(should_stay_on_reset_command);
    RUN_TEST(should_stay_when_line_just_detected);
    RUN_TEST(should_start_running);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_STRIGHT, 0);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_LEFT, 30);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_LEFT, 45);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_LEFT, 60);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_LEFT, 90);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_RIGHT, 30);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_RIGHT, 45);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_RIGHT, 60);
    RUN_PARAM_TEST(should_apply_control, CORE_CONTROL_DIRECTION_RIGHT, 90);
    return UNITY_END();
}