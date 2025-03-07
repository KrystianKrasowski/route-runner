#include <core/vehicle.h>
#include <core/types.h>
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
should_update_command(core_vehicle_state_t state,
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
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_NONE,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_BACKWARD,
                   CORE_REMOTE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_LEFT,
                   CORE_REMOTE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_RIGHT,
                   CORE_REMOTE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_MANUAL,
                   CORE_REMOTE_CONTROL_FOLLOW | CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_FORWARD,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_BACKWARD,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_BREAK,
                   CORE_REMOTE_CONTROL_BREAK);
    RUN_PARAM_TEST(should_update_command,
                   CORE_VEHICLE_STATE_LINE_DETECTED,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   CORE_REMOTE_CONTROL_FOLLOW);
    return UNITY_END();
}