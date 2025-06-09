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

    // then
    pathbot_mode_t actual_mode = pathbot_port_mock_dump_verify_mode();

    TEST_ASSERT_EQUAL(mode, actual_mode);
}

void
should_dump_pid(void)
{
    // given
    pathbot_pid_conf_t pid_conf = {
        .kp = 0.6,
        .ki = 0,
        .kd = 3.2,
    };

    p_store->pid_conf = pid_conf;

    // when
    pathbot_handle_store_dump();

    // then
    float actual_kp = pathbot_port_mock_dump_verify_pid_kp();
    float actual_ki = pathbot_port_mock_dump_verify_pid_ki();
    float actual_kd = pathbot_port_mock_dump_verify_pid_kd();

    TEST_ASSERT_EQUAL_FLOAT(pid_conf.kp, actual_kp);
    TEST_ASSERT_EQUAL_FLOAT(pid_conf.ki, actual_ki);
    TEST_ASSERT_EQUAL_FLOAT(pid_conf.kd, actual_kd);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_MANUAL);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_DETECTED);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_FOLLOWING);
    RUN_PARAM_TEST(should_dump_mode, PATHBOT_MODE_RECOVERING);

    RUN_TEST(should_dump_pid);

    return UNITY_END();
}
