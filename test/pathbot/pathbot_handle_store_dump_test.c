#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <pathbot/port_mock_dump.h>
#include <pathbot/store.h>
#include <unity.h>
#include <unity_config.h>

static pathbot_store_t *p_store;

void
setUp(void)
{
    pathbot_port_mock_dump_reset();

    pathbot_store_init(NULL);
    p_store = pathbot_store_get();
}

void
tearDown(void)
{
}

void
should_dump_mode(pathbot_mode_t const mode)
{
    // given
    p_store->mode = mode;

    // when
    pathbot_handle_store_dump();
    pathbot_mode_t actual_mode = pathbot_port_mock_dump_verify_mode();

    // then
    TEST_ASSERT_EQUAL(mode, actual_mode);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_MANUAL);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_DETECTED);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_FOLLOWING);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_RECOVERING);

    return UNITY_END();
}
