#include <core.h>
#include <unity.h>
#include <unity_config.h>

#define ON_THE_LINE  (CORE_COORDS_LINE_DETECTION_TRESHOLD)
#define OFF_THE_LINE (CORE_COORDS_LINE_DETECTION_TRESHOLD - 1)

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
    core_mode_t mode = core_vehicle_get_mode(&vehicle);
    TEST_ASSERT_EQUAL(CORE_MODE_MANUAL, mode);
}

void
should_detect_mode_change_on_init(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_detect_mode_change_on_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_mode(&vehicle, CORE_MODE_MANUAL);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);

    // then
    TEST_ASSERT_TRUE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_detect_mode_change_without_transition(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);
    core_vehicle_set_mode(&vehicle, CORE_MODE_LINE_DETECTED);

    // then
    TEST_ASSERT_FALSE(core_vehicle_is_mode_changed(&vehicle));
}

void
should_init_starting_coords(void)
{
    // given
    core_vehicle_t vehicle;

    // when
    core_vehicle_init(&vehicle);
    core_coords_t coords = core_vehicle_get_coords(&vehicle);

    // then
    TEST_ASSERT_EQUAL(0,
                      core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_3));
    TEST_ASSERT_EQUAL(0,
                      core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_2));
    TEST_ASSERT_EQUAL(0,
                      core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_1));
    TEST_ASSERT_EQUAL(
        0, core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_1));
    TEST_ASSERT_EQUAL(
        0, core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_2));
    TEST_ASSERT_EQUAL(
        0, core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_3));
}

void
should_detect_line(uint8_t left3,
                   uint8_t left2,
                   uint8_t left1,
                   uint8_t right1,
                   uint8_t right2,
                   uint8_t right3,
                   bool    expected_result)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_coords_t coords =
        core_coords_create(left3, left2, left1, right1, right2, right3);

    core_vehicle_update_coords(&vehicle, coords);

    // then
    TEST_ASSERT_EQUAL(expected_result, core_vehicle_is_line_detected(&vehicle));
}

void
should_compute_position_error(uint8_t left3,
                              uint8_t left2,
                              uint8_t left1,
                              uint8_t right1,
                              uint8_t right2,
                              uint8_t right3,
                              int16_t expected_error)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_coords_t coords =
        core_coords_create(left3, left2, left1, right1, right2, right3);

    core_vehicle_update_coords(&vehicle, coords);
    core_vehicle_update_position_error(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_error,
                      core_vehicle_last_position_error(&vehicle));
}

void
should_set_last_error_when_drifting_off_line(void)
{
    // given
    core_coords_t last_on_line = core_coords_create(5, 0, 0, 0, 0, 0);
    core_coords_t lost_line    = core_coords_create(0, 0, 0, 0, 0, 0);

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    core_vehicle_update_coords(&vehicle, last_on_line);
    core_vehicle_update_position_error(&vehicle);

    // when
    core_vehicle_update_coords(&vehicle, lost_line);
    core_vehicle_update_position_error(&vehicle);

    // then
    TEST_ASSERT_EQUAL(-100, core_vehicle_last_position_error(&vehicle));
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_init_vehicle_mode);
    RUN_TEST(should_detect_mode_change_on_init);
    RUN_TEST(should_detect_mode_change_on_transition);
    RUN_TEST(should_detect_mode_change_without_transition);
    RUN_TEST(should_init_starting_coords);
    RUN_PARAM_TEST(should_detect_line, ON_THE_LINE, 0, 0, 0, 0, 0, true);
    RUN_PARAM_TEST(should_detect_line, 0, ON_THE_LINE, 0, 0, 0, 0, true);
    RUN_PARAM_TEST(should_detect_line, 0, 0, ON_THE_LINE, 0, 0, 0, true);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, ON_THE_LINE, 0, 0, true);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, 0, ON_THE_LINE, 0, true);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, 0, 0, ON_THE_LINE, true);
    RUN_PARAM_TEST(should_detect_line, OFF_THE_LINE, 0, 0, 0, 0, 0, false);
    RUN_PARAM_TEST(should_detect_line, 0, OFF_THE_LINE, 0, 0, 0, 0, false);
    RUN_PARAM_TEST(should_detect_line, 0, 0, OFF_THE_LINE, 0, 0, 0, false);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, OFF_THE_LINE, 0, 0, false);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, 0, OFF_THE_LINE, 0, false);
    RUN_PARAM_TEST(should_detect_line, 0, 0, 0, 0, 0, OFF_THE_LINE, false);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 0, 0, 0);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 100, 100, 0, 0, 0);
    RUN_PARAM_TEST(should_compute_position_error, 0, 50, 100, 100, 0, 0, -8);
    RUN_PARAM_TEST(should_compute_position_error, 0, 60, 100, 90, 0, 0, -10);
    RUN_PARAM_TEST(should_compute_position_error, 50, 50, 100, 0, 0, 0, -45);
    RUN_PARAM_TEST(should_compute_position_error, 100, 0, 0, 0, 0, 0, -100);
    RUN_PARAM_TEST(should_compute_position_error, 70, 0, 0, 0, 0, 0, -100);
    RUN_PARAM_TEST(should_compute_position_error, 70, 20, 0, 0, 0, 0, -86);
    RUN_PARAM_TEST(should_compute_position_error, 40, 0, 0, 0, 0, 0, -100);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 100, 100, 50, 0, 8);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 90, 100, 60, 0, 10);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 100, 50, 50, 45);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 0, 100, 100);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 0, 70, 100);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 0, 40, 100);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 50, 100, 50, 50);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 100, 100, 70);
    RUN_PARAM_TEST(should_compute_position_error, 0, 0, 0, 0, 50, 100, 80);
    RUN_TEST(should_set_last_error_when_drifting_off_line);
    return UNITY_END();
}