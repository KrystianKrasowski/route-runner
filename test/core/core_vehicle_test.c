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
should_detect_line(uint8_t left,
                   uint8_t middle,
                   uint8_t right,
                   bool    expected_result)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_position_t position = {left, middle, right};
    core_vehicle_set_line_position(&vehicle, position);

    // then
    TEST_ASSERT_EQUAL(expected_result, core_vehicle_is_line_detected(&vehicle));
}

void
should_compute_position_error(uint8_t left,
                              uint8_t middle,
                              uint8_t right,
                              int8_t  expected_error)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    // when
    core_position_t position = {left, middle, right};
    core_vehicle_set_line_position(&vehicle, position);
    core_vehicle_update_position_error(&vehicle);

    // then
    TEST_ASSERT_EQUAL(expected_error,
                      core_vehicle_get_position_error(&vehicle));
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
    RUN_PARAM_TEST(should_detect_line, 10, 100, 10, true);
    RUN_PARAM_TEST(should_detect_line, 10, 110, 10, true);
    RUN_PARAM_TEST(should_detect_line, 10, 120, 10, true);
    RUN_PARAM_TEST(should_detect_line, 10, 110, 50, true);
    RUN_PARAM_TEST(should_detect_line, 50, 110, 10, true);
    RUN_PARAM_TEST(should_detect_line, 40, 90, 10, false);
    RUN_PARAM_TEST(should_detect_line, 10, 80, 70, false);
    RUN_PARAM_TEST(should_detect_line, 10, 50, 80, false);
    RUN_PARAM_TEST(should_detect_line, 100, 100, 100, false);
    RUN_PARAM_TEST(should_compute_position_error, 10, 100, 10, 0);
    RUN_PARAM_TEST(should_compute_position_error, 10, 100, 19, 9);
    RUN_PARAM_TEST(should_compute_position_error, 19, 100, 10, -9);
    RUN_PARAM_TEST(should_compute_position_error, 50, 43, 10, -40);
    RUN_PARAM_TEST(should_compute_position_error, 10, 33, 60, 50);
    return UNITY_END();
}