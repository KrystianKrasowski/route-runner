#include <core/vehicle.h>
#include <unity.h>
#include <unity_config.h>

#define COORDS_ON_LINE  core_coords_create(0, 0, 100, 100, 0, 0)
#define COORDS_OFF_LINE core_coords_create(0, 0, 0, 0, 0, 0)

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_init_vehicle_mode(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    core_mode_value_t value = core_vehicle_get_mode_value(&vehicle);
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, value);
}

void
should_update_manual_mode(core_coords_t     coords,
                          core_mode_value_t expected_mode,
                          bool              mode_changed)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_MANUAL);

    // when
    core_vehicle_update_coords(&vehicle, coords);
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_mode, core_vehicle_get_mode_value(&vehicle));
    TEST_ASSERT_EQUAL(mode_changed, core_vehicle_is_mode_changed(&vehicle));
}

void
should_update_line_detected_mode(uint16_t          commands,
                                 core_coords_t     coords,
                                 core_mode_value_t expected_mode,
                                 bool              mode_changed)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_DETECTED);

    // when
    core_vehicle_update_commands(&vehicle, commands);
    core_vehicle_update_coords(&vehicle, coords);
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_mode, core_vehicle_get_mode_value(&vehicle));
    TEST_ASSERT_EQUAL(mode_changed, core_vehicle_is_mode_changed(&vehicle));
}

void
should_update_line_following_mode(uint16_t          commands,
                                  core_coords_t     coords,
                                  core_mode_value_t expected_mode,
                                  uint16_t          expected_commands,
                                  bool              mode_changed)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode_value(&vehicle, CORE_MODE_LINE_FOLLOWING);

    // when
    core_vehicle_update_commands(&vehicle, commands);
    core_vehicle_update_coords(&vehicle, coords);
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_mode, core_vehicle_get_mode_value(&vehicle));
    TEST_ASSERT_EQUAL(expected_commands, core_vehicle_get_command(&vehicle));
    TEST_ASSERT_EQUAL(mode_changed, core_vehicle_is_mode_changed(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_init_vehicle_mode);

    RUN_PARAM_TEST(should_update_manual_mode,
                   COORDS_ON_LINE,
                   CORE_MODE_LINE_DETECTED,
                   true);

    RUN_PARAM_TEST(
        should_update_manual_mode, COORDS_OFF_LINE, CORE_MODE_MANUAL, false);

    RUN_PARAM_TEST(should_update_line_detected_mode,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   COORDS_ON_LINE,
                   CORE_MODE_LINE_FOLLOWING,
                   true);
    RUN_PARAM_TEST(should_update_line_detected_mode,
                   CORE_REMOTE_CONTROL_NONE,
                   COORDS_ON_LINE,
                   CORE_MODE_LINE_DETECTED,
                   false);
    RUN_PARAM_TEST(should_update_line_detected_mode,
                   CORE_REMOTE_CONTROL_NONE,
                   COORDS_OFF_LINE,
                   CORE_MODE_MANUAL,
                   true);

    RUN_PARAM_TEST(should_update_line_following_mode,
                   CORE_REMOTE_CONTROL_BREAK,
                   COORDS_ON_LINE,
                   CORE_MODE_MANUAL,
                   CORE_REMOTE_CONTROL_BREAK,
                   true);

    RUN_PARAM_TEST(should_update_line_following_mode,
                   CORE_REMOTE_CONTROL_FOLLOW,
                   COORDS_OFF_LINE,
                   CORE_MODE_MANUAL,
                   CORE_REMOTE_CONTROL_NONE,
                   true);

    RUN_PARAM_TEST(should_update_line_following_mode,
                   CORE_REMOTE_CONTROL_NONE,
                   COORDS_ON_LINE,
                   CORE_MODE_LINE_FOLLOWING,
                   CORE_REMOTE_CONTROL_NONE,
                   false);
                   
    return UNITY_END();
}