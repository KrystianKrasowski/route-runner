#include <pathbot/domain.h>
#include <pathbot/fixtures.h>
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
    pathbot_mode_t mode   = PATHBOT_MODE_MANUAL;
    pathbot_mode_t actual = pathbot_update_mode_tracking(NULL, &mode);

    // then
    TEST_ASSERT_EQUAL(PATHBOT_MODE_MANUAL, actual);
}

void
should_update_tracking_mode(pathbot_mode_t   mode,
                            pathbot_coords_t coords,
                            pathbot_mode_t   expected_mode,
                            bool             b_expected_changed)
{
    // when
    bool b_changed = pathbot_update_mode_tracking(&coords, &mode);

    // then
    TEST_ASSERT_EQUAL(expected_mode, mode);
    TEST_ASSERT_EQUAL(b_expected_changed, b_changed);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_keep_mode_on_null_coords);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_ON_FINISH,
                   PATHBOT_MODE_MANUAL,
                   true);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_MANUAL,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_MANUAL,
                   false);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_DETECTED,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_DETECTED,
                   false);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_FOLLOWING,
                   FIXTURES_COORDS6_ON_ROUTE,
                   PATHBOT_MODE_FOLLOWING,
                   false);

    RUN_PARAM_TEST(should_update_tracking_mode,
                   PATHBOT_MODE_RECOVERING,
                   FIXTURES_COORDS6_OFF_ROUTE,
                   PATHBOT_MODE_RECOVERING,
                   false);

    return UNITY_END();
}
