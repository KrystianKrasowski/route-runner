#include "dualshock2.h"
#include "gpio.h"
#include "spi.h"
#include "tim2.h"
#include <mq.h>
#include <stdint.h>

static spi_request_t request = {
    .payload       = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .size          = 9,
    .device_select = {GPIO_DUALSHOCK2_ATTENTION},
};

static volatile uint16_t last_command = DS2_NONE;

void
dualshock2_init(void)
{
    last_command = DS2_NONE;
    gpio_init(&request.device_select);
    gpio_set_state(&request.device_select, GPIO_STATE_HIGH);
    spi_init_master();
    tim2_ch1_init();
}

void
tim2_ch1_compare_isr(void)
{
    spi_transmittion_start(&request);
}

void
spi_on_response_received_isr(uint8_t response[])
{
    uint16_t command;

    if (response[0] != 0xff || (response[1] != 0x41 && response[1] != 0x73) ||
        response[2] != 0x5a)
    {
        command = DS2_NONE;
    }
    else
    {
        command = ~(((uint16_t)response[4] << 8) | response[3]);
    }

    if (last_command != command)
    {
        last_command            = command;
        mq_message_t message = mq_create_command_message(command);
        mq_push(MQ_TOPIC_REMOTE_CONTROL, message);
    }
}