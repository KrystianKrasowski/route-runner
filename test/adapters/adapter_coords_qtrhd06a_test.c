#include <adapters/coords_qtrhd06a.h>
#include <devices/qtrhd06a.h>
#include <devices/qtrhd06a_mock.h>
#include <pathbot/domain.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/result.h>

void
setUp(void)
{
    device_qtrhd06a_mock_init();
}

void
tearDown(void)
{
    device_qtrhd06a_mock_deinit();
}

void
should_return_not_ready(bool b_ready, int expected_result)
{
    // given
    pathbot_coords_t h_coords;
    device_qtrhd06a_mock_set_ready(DEVICE_QTRHD06A_1, b_ready);

    // when
    int result = adapter_coords_qtrhd06a_read(DEVICE_QTRHD06A_1, &h_coords);

    // then
    TEST_ASSERT_EQUAL(expected_result, result);
}

/*
 * With OOP there is not convinient way to test the coords values without
 * exposing some "equals" function from coords module. I don't think it is good
 * enough reason to extend api just for the sake of test. Maybe DOD is the
 * answer.
 */

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_return_not_ready, false, RESULT_NOT_READY);
    RUN_PARAM_TEST(should_return_not_ready, true, RESULT_OK);

    return UNITY_END();
}
