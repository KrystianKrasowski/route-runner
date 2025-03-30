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
    TEST_ASSERT_EQUAL(expected_result,
                      core_position_is_line_detected(&position));
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
    return UNITY_END();
}