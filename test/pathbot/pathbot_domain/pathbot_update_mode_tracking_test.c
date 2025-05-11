#include "fixtures.h"
#include <pathbot/domain.h>
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
should_keep_mode_on_null_coords(void)
{
    // when
    pathbot_mode_t actual =
        pathbot_update_mode_tracking(PATHBOT_MODE_MANUAL, NULL);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_MODE_MANUAL, actual);
}

void
should_update_tracking_mode(pathbot_mode_t   current_mode,
                            pathbot_coords_t coords,
                            pathbot_mode_t   expected)
{
    // when
    pathbot_mode_t actual = pathbot_update_mode_tracking(current_mode, &coords);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_keep_mode_on_null_coords);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING);

    return UNITY_END();
}
