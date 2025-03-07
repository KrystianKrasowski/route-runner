#include <core.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_init_vehicle_state(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    core_vehicle_state_t state = core_vehicle_get_state(&vehicle);
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL, state);
}

void
should_detect_state_change_on_init(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_state_changed(&vehicle));
}

void
should_detect_state_change_on_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_MANUAL);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_state_changed(&vehicle));
}

void
should_detect_state_change_without_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);

    // then
    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

void
should_init_starting_position(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    TEST_ASSERT_EQUAL(0, vehicle.position.left);
    TEST_ASSERT_EQUAL(0, vehicle.position.middle);
    TEST_ASSERT_EQUAL(0, vehicle.position.right);
}

void
should_detect_line(bool result, uint8_t left, uint8_t middle, uint8_t right)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_position_t position = {left, middle, right};
    core_vehicle_set_line_position(&vehicle, position);

    // then
    TEST_ASSERT_EQUAL(result, core_vehicle_is_line_detected(&vehicle));
}

void
should_update_motion_while_in_manual_state(core_motion_direction_t direction,
                                           int8_t                  correction,
                                           uint16_t                command)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_MANUAL);

    // when
    core_vehicle_set_command(&vehicle, command);
    core_vehicle_result_t result = core_vehicle_update_motion(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_MOTION_CHANGED, result);
    TEST_ASSERT_EQUAL(direction, core_vehicle_get_motion_direction(&vehicle));
    TEST_ASSERT_EQUAL(correction, core_vehicle_get_motion_correction(&vehicle));
}

void
should_apply_remote_control(core_vehicle_state_t state,
                            uint16_t             command,
                            uint16_t             expected_command)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, state);

    // when
    core_vehicle_update_command(&vehicle, command);

    // then
    TEST_ASSERT_EQUAL(expected_command, core_vehicle_get_command(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_vehicle_state);
    RUN_TEST(should_detect_state_change_on_init);
    RUN_TEST(should_detect_state_change_on_transition);
    RUN_TEST(should_detect_state_change_without_transition);
    RUN_TEST(should_init_starting_position);
    RUN_PARAM_TEST(should_detect_line, true, 10, 100, 10);
    RUN_PARAM_TEST(should_detect_line, true, 10, 110, 10);
    RUN_PARAM_TEST(should_detect_line, true, 10, 120, 10);
    RUN_PARAM_TEST(should_detect_line, true, 10, 110, 50);
    RUN_PARAM_TEST(should_detect_line, true, 50, 110, 10);
    RUN_PARAM_TEST(should_detect_line, false, 40, 90, 10);
    RUN_PARAM_TEST(should_detect_line, false, 10, 80, 70);
    RUN_PARAM_TEST(should_detect_line, false, 10, 50, 80);
    RUN_PARAM_TEST(should_detect_line, false, 100, 100, 100);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_FORWARD,
                   0,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_FORWARD,
                   -90,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_FORWARD,
                   90,
                   CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_BACKWARD,
                   0,
                   CORE_REMOTE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_BACKWARD,
                   -90,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_motion_while_in_manual_state,
                   CORE_MOTION_BACKWARD,
                   90,
                   CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_NONE,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_BACKWARD,
                   CORE_REMOTE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_LEFT,
                   CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_RIGHT,
                   CORE_REMOTE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FOLLOW | CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_BACKWARD,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_BREAK,
                   CORE_REMOTE_CONTROL_BREAK);
    RUN_PARAM_TEST(should_apply_remote_control,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_FOLLOW);
    return UNITY_END();
}