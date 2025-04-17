#include <adc_mock.h>
#include <mq.h>
#include <qtrhd06a.h>
#include <unity.h>

void
setUp(void)
{
    mq_init();
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
    uint16_t conversions[40] = {
        5906,  28946, 28945, 6417,  5906,  28945, 28945, 6417,  5906,  29202,
        28945, 6418,  5906,  28945, 28945, 6417,  5906,  28945, 28946, 6418,
        5906,  28946, 28945, 6417,  5906,  29202, 28945, 6417,  5906,  28945,
        28945, 6417,  5906,  28945, 28945, 6417,  5906,  28945, 28946, 6418,
    };

    mq_message_t message;

    // when
    adc_sequence_complete_isr(conversions);
    int status = mq_pull(MQ_TOPIC_COORDS, &message);

    // then
    uint8_t expected_coords[6];
    qtrhd06a_parse_values(message.payload, expected_coords);

    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL(25, expected_coords[0]);
    TEST_ASSERT_EQUAL(113, expected_coords[1]);
    TEST_ASSERT_EQUAL(113, expected_coords[2]);
    TEST_ASSERT_EQUAL(23, expected_coords[3]);
    TEST_ASSERT_EQUAL(17, expected_coords[4]);
    TEST_ASSERT_EQUAL(18, expected_coords[5]);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_line_sensor);
    RUN_TEST(should_average_adc_conversions);
    return UNITY_END();
}