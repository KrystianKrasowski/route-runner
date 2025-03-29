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
should_stay_manual(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 0, 0, 0, 0, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, core_vehicle_get_mode(&vehicle));
    TEST_ASSERT_FALSE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_transit_to_line_detected_from_manual(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 10, 100, 100, 10, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_LINE_DETECTED, core_vehicle_get_mode(&vehicle));
}

void
should_stay_line_detected(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 10, 100, 100, 10, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_LINE_DETECTED, core_vehicle_get_mode(&vehicle));

    TEST_ASSERT_FALSE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_transit_to_manual_from_line_detected(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 0, 0, 0, 0, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, core_vehicle_get_mode(&vehicle));
}

void
should_transit_to_line_following_from_line_detected(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 10, 100, 100, 10, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);
    core_vehicle_update_coords(&vehicle, coords);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FOLLOW);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_LINE_FOLLOWING,
                      core_vehicle_get_mode(&vehicle));
}

void
should_transit_to_manual_from_line_following_by_remote_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_BREAK);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, core_vehicle_get_mode(&vehicle));
}

void
should_transit_to_manual_from_line_following_by_line_end(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 0, 0, 0, 0, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, core_vehicle_get_mode(&vehicle));
}

void
should_clear_command_on_line_end(void)
{
    // given
    core_coords_t coords = core_coords_create(0, 0, 0, 0, 0, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FOLLOW);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_REMOTE_CONTROL_NONE,
                      core_vehicle_get_command(&vehicle));
}

void
should_keep_following_the_line(uint8_t left, uint8_t middle, uint8_t right)
{
    // given
    core_coords_t coords =
        core_coords_create(0, left, middle, middle, right, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_FOLLOWING);
    core_vehicle_update_coords(&vehicle, coords);

    // when
    core_vehicle_update_mode(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_MODE_LINE_FOLLOWING,
                      core_vehicle_get_mode(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_stay_manual);
    RUN_TEST(should_transit_to_line_detected_from_manual);
    RUN_TEST(should_stay_line_detected);
    RUN_TEST(should_transit_to_manual_from_line_detected);
    RUN_TEST(should_transit_to_line_following_from_line_detected);
    RUN_TEST(should_transit_to_manual_from_line_following_by_remote_command);
    RUN_TEST(should_transit_to_manual_from_line_following_by_line_end);
    RUN_TEST(should_clear_command_on_line_end);
    RUN_PARAM_TEST(should_keep_following_the_line, 10, 110, 10);
    RUN_PARAM_TEST(should_keep_following_the_line, 10, 50, 50);
    RUN_PARAM_TEST(should_keep_following_the_line, 50, 50, 10);
    RUN_PARAM_TEST(should_keep_following_the_line, 70, 30, 10);
    RUN_PARAM_TEST(should_keep_following_the_line, 10, 30, 70);
    return UNITY_END();
}