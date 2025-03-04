#include <adc_mock.h>
#include <qtrhd06a.h>
#include <queue.h>
#include <unity.h>

void
setUp(void)
{
    adc_mock_reset();
}

void
tearDown(void)
{
}

void
should_initialize_line_sensor(void)
{
    // when
    qtrhd06a_init();

    // then
    TEST_ASSERT_EQUAL(1, adc_mock_verify_init_calls());
    TEST_ASSERT_EQUAL(1, adc_mock_verify_on_calls());
    TEST_ASSERT_EQUAL(1, adc_mock_verity_start_calls());
}

void
should_average_adc_conversions(void)
{
    // given
    uint8_t conversions[30] = {
        15, 20, 16, 16, 22, 15, 18, 21, 17, 17, 22, 15, 14, 19, 18,
        15, 20, 16, 16, 22, 15, 18, 21, 17, 17, 22, 15, 14, 19, 18,
    };

    queue_message_t message;

    // when
    adc_sequence_complete_isr(conversions);
    queue_status_t status = queue_pull(QUEUE_TOPIC_LINE_POSITION, &message);

    // then
    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, status);
    TEST_ASSERT_EQUAL(QUEUE_MSG_TYPE_LINE_POSITION, message.type);
    TEST_ASSERT_EQUAL(16, message.payload.line_position[0]);
    TEST_ASSERT_EQUAL(20, message.payload.line_position[1]);
    TEST_ASSERT_EQUAL(16, message.payload.line_position[2]);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_line_sensor);
    RUN_TEST(should_average_adc_conversions);
    return UNITY_END();
}