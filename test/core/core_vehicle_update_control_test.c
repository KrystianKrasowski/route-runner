#include <core/vehicle.h>
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
should_update_command(core_mode_value_t mode,
                      uint16_t          commands,
                      uint16_t          expected_command)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, mode);

    // when
    core_vehicle_update_control(&vehicle, core_control(commands));

    // then
    TEST_ASSERT_EQUAL(expected_command, core_vehicle_get_commands(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_NONE,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_FORWARD,
                   CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_BACKWARD,
                   CORE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_LEFT,
                   CORE_CONTROL_LEFT);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_RIGHT,
                   CORE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_FOLLOW,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_FOLLOW | CORE_CONTROL_FORWARD,
                   CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_BREAK | CORE_CONTROL_FORWARD,
                   CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_FORWARD | CORE_CONTROL_BACKWARD,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_MANUAL,
                   CORE_CONTROL_RIGHT | CORE_CONTROL_LEFT,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_DETECTED,
                   CORE_CONTROL_FOLLOW,
                   CORE_CONTROL_FOLLOW);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_DETECTED,
                   CORE_CONTROL_FORWARD,
                   CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_CONTROL_FORWARD,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_CONTROL_BACKWARD,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_CONTROL_FOLLOW,
                   CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_CONTROL_BREAK,
                   CORE_CONTROL_BREAK);
    RUN_PARAM_TEST(should_update_command,
                   CORE_MODE_LINE_DETECTED,
                   CORE_CONTROL_FOLLOW,
                   CORE_CONTROL_FOLLOW);
    return UNITY_END();
}