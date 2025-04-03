#include <core/position.h>
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
should_detect_line(uint8_t left3,
                   uint8_t left2,
                   uint8_t left1,
                   uint8_t right1,
                   uint8_t right2,
                   uint8_t right3,
                   bool    expected_result)
{
    // given
    core_position_t position;
    core_position_init(&position);

    // when
    core_coords_t coords =
        core_coords_create(left3, left2, left1, right1, right2, right3);

    core_position_update_coords(&position, coords);

    // then
    TEST_ASSERT_EQUAL(expected_result, core_position_is_on_route(&position));
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
    core_position_t position;
    core_position_init(&position);

    // when
    core_coords_t coords =
        core_coords_create(left3, left2, left1, right1, right2, right3);

    core_position_update_coords(&position, coords);
    core_position_update_error(&position);

    // then
    TEST_ASSERT_EQUAL(expected_error, core_position_last_error(&position));
}

void
should_set_last_error_when_drifting_off_line(void)
{
    // given
    core_coords_t last_on_line = core_coords_create(5, 0, 0, 0, 0, 0);
    core_coords_t lost_line    = core_coords_create(0, 0, 0, 0, 0, 0);

    core_position_t position;
    core_position_init(&position);

    core_position_update_coords(&position, last_on_line);
    core_position_update_error(&position);

    // when
    core_position_update_coords(&position, lost_line);
    core_position_update_error(&position);

    // then
    TEST_ASSERT_EQUAL(-100, core_position_last_error(&position));
}

int
main(void)
{
    UNITY_BEGIN();
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
    return UNITY_END();
}