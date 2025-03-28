#include <core.h>
#include <unity.h>
#include <unity_config.h>

#define ON_THE_LINE  (CORE_POSITION_DETECTION_TRESHOLD)
#define OFF_THE_LINE (CORE_POSITION_DETECTION_TRESHOLD - 1)

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
    core_position_t position = core_vehicle_get_line_position(&vehicle);

    // then
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_LEFT_3));
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_LEFT_2));
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_LEFT_1));
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_RIGHT_1));
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_RIGHT_2));
    TEST_ASSERT_EQUAL(
        0, core_position_get_by_place(&position, CORE_POSITION_PLACE_RIGHT_3));
}

void
should_detect_line(uint8_t left_3,
                   uint8_t left_2,
                   uint8_t left_1,
                   uint8_t right_1,
                   uint8_t right_2,
                   uint8_t right_3,
                   bool    expected_result)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_position_t position = {
        left_3, left_2, left_1, right_1, right_2, right_3};
    core_vehicle_set_line_position(&vehicle, position);

    // then
    TEST_ASSERT_EQUAL(expected_result, core_vehicle_is_line_detected(&vehicle));
}

void
should_compute_position_error(uint8_t left_3,
                              uint8_t left_2,
                              uint8_t left_1,
                              uint8_t right_1,
                              uint8_t right_2,
                              uint8_t right_3,
                              int16_t expected_error)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_position_t position = {
        left_3, left_2, left_1, right_1, right_2, right_3};
    core_vehicle_set_line_position(&vehicle, position);
    core_vehicle_update_position_error(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_error,
                      core_vehicle_get_position_error(&vehicle));
}

void
should_set_last_error_when_drifting_off_line(void)
{
    // given
    core_position_t last_on_line_position = {5, 0, 0, 0, 0, 0};
    core_position_t line_lost_position    = {0, 0, 0, 0, 0, 0};
    core_vehicle_t vehicle;

    core_vehicle_init(&vehicle);
    core_vehicle_set_line_position(&vehicle, last_on_line_position);
    core_vehicle_update_position_error(&vehicle);

    // when
    core_vehicle_set_line_position(&vehicle, line_lost_position);
    core_vehicle_update_position_error(&vehicle);

    // then
    TEST_ASSERT_EQUAL(-100, core_vehicle_get_position_error(&vehicle));
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