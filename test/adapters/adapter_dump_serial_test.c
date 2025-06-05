#include <adapters/dump_serial.h>
#include <devices/serial_in_mock.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

void
setUp(void)
{
    device_serial_in_mock_init();
}

void
tearDown(void)
{
    device_serial_in_mock_deinit();
}

void
should_read_domain_dump_request(char command, int expected_result)
{
    // given
    device_serial_in_mock_set_requested(DEVICE_SERIAL_IN_1, command);

    // when
    int result = adapter_domain_dump_request_read();

    // then
    TEST_ASSERT_EQUAL(expected_result, result);
}

void
should_return_ok(void)
{
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_read_domain_dump_request, 'd', RESULT_OK);
    RUN_PARAM_TEST(should_read_domain_dump_request, 'a', RESULT_NOT_READY);
    RUN_PARAM_TEST(should_read_domain_dump_request, 'b', RESULT_NOT_READY);
    RUN_PARAM_TEST(should_read_domain_dump_request, 'c', RESULT_NOT_READY);
    RUN_PARAM_TEST(should_read_domain_dump_request, 'e', RESULT_NOT_READY);

    return UNITY_END();
}
