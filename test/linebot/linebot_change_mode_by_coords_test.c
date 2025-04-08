#include "fixtures.h"
#include <linebot.h>
#include <linebot_port_mock_mode.h>
#include <unity.h>
#include <unity_config.h>

static linebot_t linebot;

void
setUp(void)
{
    linebot_port_mock_mode_init();
    linebot_init();
}

void
tearDown(void)
{
}

void
should_change_mode(linebot_mode_t   current_mode,
                   linebot_coords_t coords,
                   linebot_mode_t   expected_mode)
{
    // given
    linebot = fixtures_linebot_acquire(current_mode);

    // when
    linebot_change_mode_by_coords(linebot, coords);

    // then
    linebot_mode_t applied_mode = linebot_port_mock_mode_get_changed_mode();
    TEST_ASSERT_EQUAL(expected_mode, linebot_get_mode(linebot));
    TEST_ASSERT_EQUAL(expected_mode, applied_mode);
    TEST_ASSERT_EQUAL(1, linebot_port_mock_mode_verify_changed_calls());
}

void
should_keep_mode(linebot_mode_t mode, linebot_coords_t coords)
{
    // given
    linebot = fixtures_linebot_acquire(mode);

    // when
    linebot_change_mode_by_coords(linebot, coords);

    // then
    TEST_ASSERT_EQUAL(mode, linebot_get_mode(linebot));
    TEST_ASSERT_EQUAL(0, linebot_port_mock_mode_verify_changed_calls());
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_MANUAL,
                   fixtures_coords_acquire_on_route(),
                   LINEBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_DETECTED,
                   fixtures_coords_acquire_off_route(),
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_FOLLOWING,
                   fixtures_coords_acquire_off_route(),
                   LINEBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_RECOVERING,
                   fixtures_coords_acquire_on_route(),
                   LINEBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_FOLLOWING,
                   fixtures_coords_acquire_on_finish(),
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_change_mode,
                   LINEBOT_MODE_RECOVERING,
                   fixtures_coords_acquire_on_finish(),
                   LINEBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_keep_mode,
                   LINEBOT_MODE_MANUAL,
                   fixtures_coords_acquire_off_route());

    RUN_PARAM_TEST(should_keep_mode,
                   LINEBOT_MODE_DETECTED,
                   fixtures_coords_acquire_on_route());

    RUN_PARAM_TEST(should_keep_mode,
                   LINEBOT_MODE_FOLLOWING,
                   fixtures_coords_acquire_on_route());

    RUN_PARAM_TEST(should_keep_mode,
                   LINEBOT_MODE_RECOVERING,
                   fixtures_coords_acquire_off_route());

    return UNITY_END();
}