#include <adc_mock.h>
#include <qtrhd06a.h>
#include <mq.h>
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
    uint32_t conversions[40] = {
        7798798, 7864333, 1048576, 917504, 7536656, 7667726, 983040,  851968,
        7733262, 7602190, 917504,  917504, 7602190, 7667727, 851968,  786432,
        7733262, 7667728, 917504,  851968, 7798798, 7864333, 1048576, 917504,
        7536656, 7667726, 983040,  851968, 7733262, 7602190, 917504,  917504,
        7602190, 7667727, 851968,  786432, 7733262, 7667728, 917504,  851968,
    };

    mq_message_t message;

    // when
    adc_sequence_complete_isr(conversions);
    mq_status_t status = mq_pull(MQ_TOPIC_LINE_POSITION, &message);

    // then
    TEST_ASSERT_EQUAL(MQ_SUCCESS, status);
    TEST_ASSERT_EQUAL(MQ_MESSAGE_TYPE_LINE_POSITION, message.type);
    TEST_ASSERT_EQUAL(13, message.payload.line_position[0]);
    TEST_ASSERT_EQUAL(14, message.payload.line_position[1]);
    TEST_ASSERT_EQUAL(117, message.payload.line_position[2]);
    TEST_ASSERT_EQUAL(117, message.payload.line_position[3]);
    TEST_ASSERT_EQUAL(14, message.payload.line_position[4]);
    TEST_ASSERT_EQUAL(14, message.payload.line_position[5]);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_line_sensor);
    RUN_TEST(should_average_adc_conversions);
    return UNITY_END();
}