#include <dualshock2.h>
#include <gpio_mock.h>
#include <queue.h>
#include <spi_mock.h>
#include <tim3_mock.h>
#include <unity.h>
#include <unity_config.h>

#define ATTENTION_PIN GPIO_DUALSHOCK2_ATTENTION

#define TEST_ASSERT_DS2_COMMANDS(cmd, state) TEST_ASSERT_BITS_HIGH(cmd, state)

void
setUp(void)
{
    dualshock2_init();
}

void
tearDown(void)
{
    gpio_mock_reset();
    spi_mock_reset();
    tim3_ch1_mock_reset();
}

void
should_initialize_attention_gpio(void)
{
    // then
    TEST_ASSERT_TRUE(gpio_mock_verify_pin_init(ATTENTION_PIN));
    TEST_ASSERT_EQUAL(GPIO_STATE_HIGH, gpio_mock_get_state(ATTENTION_PIN));
}

void
should_initialize_spi_master(void)
{
    // then
    TEST_ASSERT_EQUAL(1, spi_mock_verify_init_master_calls());
}

void
should_initialize_timer3_channel1(void)
{
    // then
    TEST_ASSERT_EQUAL(1, tim3_ch1_mock_verify_init_calls());
}

void
should_start_spi_transmission(void)
{
    // when
    tim3_ch1_compare_isr();

    // then
    uint8_t request[] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TEST_ASSERT_TRUE(spi_mock_verify_transmission_start_request(request, 9));
}

void
should_receive_spi_transmission(uint8_t response[], uint16_t expected_command)
{
    // when
    spi_on_response_received_isr(response);

    // then
    queue_message_t message;
    queue_status_t  status = queue_pull(QUEUE_TOPIC_REMOTE_CONTROL, &message);

    TEST_ASSERT_EQUAL(QUEUE_SUCCESS, status);
    TEST_ASSERT_DS2_COMMANDS(expected_command, message.payload.command);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_attention_gpio);
    RUN_TEST(should_initialize_spi_master);
    RUN_TEST(should_initialize_timer3_channel1);
    RUN_TEST(should_start_spi_transmission);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_SELECT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_L3);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_R3);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_START);
    
    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_UP);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_RIGHT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_DOWN);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff},
        DS2_LEFT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff},
        DS2_L2);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff},
        DS2_R2);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff},
        DS2_L1);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff},
        DS2_R1);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff},
        DS2_TRIANGLE);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff},
        DS2_CIRCLE);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff},
        DS2_CROSS);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff},
        DS2_SQUARE);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xdf, 0xfd, 0xff, 0xff, 0xff, 0xff},
        DS2_R2 | DS2_RIGHT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0x7f, 0xfd, 0xff, 0xff, 0xff, 0xff},
        DS2_R2 | DS2_LEFT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0xdf, 0xfe, 0xff, 0xff, 0xff, 0xff},
        DS2_L2 | DS2_RIGHT);

    RUN_PARAM_TEST(
        should_receive_spi_transmission,
        (uint8_t[]){0xff, 0x41, 0x5a, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff},
        DS2_L2 | DS2_LEFT);

    return UNITY_END();
}