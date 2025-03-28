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
    core_position_t position = {0, 0, 0, 0, 0, 0};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

void
should_transit_to_line_detected_from_manual(void)
{
    // given
    core_position_t position = {10, 110, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_DETECTED,
                      core_vehicle_get_state(&vehicle));
}

void
should_stay_line_detected(void)
{
    // given
    core_position_t position = {10, 110, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_DETECTED,
                      core_vehicle_get_state(&vehicle));

    TEST_ASSERT_FALSE(core_vehicle_is_state_changed(&vehicle));
}

void
should_transit_to_manual_from_line_detected(void)
{
    // given
    core_position_t position = {0, 0, 0, 0, 0, 0};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
}

void
should_transit_to_line_following_from_line_detected(void)
{
    // given
    core_position_t position = {10, 110, 10};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    core_vehicle_set_line_position(&vehicle, position);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FOLLOW);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_FOLLOWING,
                      core_vehicle_get_state(&vehicle));
}

void
should_transit_to_manual_from_line_following_by_remote_command(void)
{
    // given
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_BREAK);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
}

void
should_transit_to_manual_from_line_following_by_line_end(void)
{
    // given
    core_position_t position = {0, 0, 0, 0, 0, 0};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_MANUAL,
                      core_vehicle_get_state(&vehicle));
}

void
should_clear_command_on_line_end(void)
{
    // given
    core_position_t position = {0, 0, 0, 0, 0, 0};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    core_vehicle_set_command(&vehicle, CORE_REMOTE_CONTROL_FOLLOW);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_REMOTE_CONTROL_NONE,
                      core_vehicle_get_command(&vehicle));
}

void
should_keep_following_the_line(uint8_t left, uint8_t middle, uint8_t right)
{
    // given
    core_position_t position = {left, middle, right};

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_vehicle_set_state(&vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    core_vehicle_set_line_position(&vehicle, position);

    // when
    core_vehicle_update_state(&vehicle);

    // then
    TEST_ASSERT_EQUAL(CORE_VEHICLE_STATE_LINE_FOLLOWING,
                      core_vehicle_get_state(&vehicle));
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