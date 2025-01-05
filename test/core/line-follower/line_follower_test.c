#include "line-follower.h"
#include "unity.h"

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_run(void)
{
    // when
    line_follower_run();

    // then
    TEST_ASSERT_FALSE(line_follower_is_standby());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_run);
    return UNITY_END();
}