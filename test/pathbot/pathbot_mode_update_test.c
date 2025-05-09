#include <pathbot.h>
#include <unity.h>
#include <unity_config.h>

static pathbot_coords_t const COORDS_ON_ROUTE = {
    .coords  = {0, 0, 100, 100, 0, 0},
    .weights = PATHBOT_COORDS_WEIGHTS_6,
    .length  = 6,
};

static pathbot_coords_t const COORDS_OFF_ROUTE = {
    .coords  = {0, 0, 0, 0, 0, 0},
    .weights = PATHBOT_COORDS_WEIGHTS_6,
    .length  = 6,
};

static pathbot_coords_t const COORDS_ON_FINISH = {
    .coords  = {5, 0, 0, 0, 0, 5},
    .weights = PATHBOT_COORDS_WEIGHTS_6,
    .length  = 6,
};

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_update_manual_mode(pathbot_mode_t current,
                          uint16_t       commands,
                          pathbot_mode_t expected)
{
    // when
    pathbot_mode_t actual = pathbot_update_mode_manual(current, commands);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

void
should_update_tracking_mode(pathbot_mode_t   current,
                            pathbot_coords_t coords,
                            pathbot_mode_t   expected)
{
    // when
    pathbot_mode_t actual = pathbot_update_mode_tracking(current, &coords);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_MANUAL,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_NONE,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FORWARD,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BACKWARD,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_LEFT,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_RIGHT,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_DETECTED,
                   PATHBOT_COMMAND_FOLLOW,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_FOLLOWING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_manual_mode,
                   PATHBOT_MODE_RECOVERING,
                   PATHBOT_COMMAND_BREAK,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   COORDS_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   COORDS_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   COORDS_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   COORDS_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   COORDS_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   COORDS_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   COORDS_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   COORDS_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   COORDS_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   COORDS_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    return UNITY_END();
}
