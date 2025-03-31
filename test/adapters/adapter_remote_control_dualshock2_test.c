#include <core.h>
#include <dualshock2.h>
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
should_map_dualshock2(uint16_t dualshock2_command, uint16_t expected_command)
{
    // when
    uint16_t actual = core_port_remote_control_map(dualshock2_command);

    // then
    TEST_ASSERT_EQUAL(expected_command, actual);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_PARAM_TEST(should_map_dualshock2, DS2_NONE, CORE_CONTROL_NONE);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_R2, CORE_CONTROL_FORWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_L2, CORE_CONTROL_BACKWARD);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_RIGHT, CORE_CONTROL_RIGHT);
    RUN_PARAM_TEST(should_map_dualshock2, DS2_LEFT, CORE_CONTROL_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_RIGHT,
                   CORE_CONTROL_FORWARD | CORE_CONTROL_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_R2 | DS2_LEFT,
                   CORE_CONTROL_FORWARD | CORE_CONTROL_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_RIGHT,
                   CORE_CONTROL_BACKWARD | CORE_CONTROL_RIGHT);

    RUN_PARAM_TEST(should_map_dualshock2,
                   DS2_L2 | DS2_LEFT,
                   CORE_CONTROL_BACKWARD | CORE_CONTROL_LEFT);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_L2 | DS2_R2, CORE_CONTROL_NONE);

    RUN_PARAM_TEST(
        should_map_dualshock2, DS2_RIGHT | DS2_LEFT, CORE_CONTROL_NONE);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CIRCLE, CORE_CONTROL_BREAK);

    RUN_PARAM_TEST(should_map_dualshock2, DS2_CROSS, CORE_CONTROL_FOLLOW);
    return UNITY_END();
}