#include "dualshock2.h"
#include "gpio.h"
#include "spi.h"
#include "tim3.h"
#include <queue.h>
#include <stdint.h>

static spi_request_t const request = {
    .payload = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .size    = 9};

static volatile uint16_t last_command = DS2_NONE;
static gpio_t            attention    = {GPIO_DUALSHOCK2_ATTENTION};

void
dualshock2_init(void)
{
    last_command = DS2_NONE;
    gpio_init(&attention);
    gpio_set_state(&attention, GPIO_STATE_HIGH);
    spi_init_master();
    tim3_ch1_init();
}

void
tim3_ch1_compare_isr(void)
{
    gpio_set_state(&attention, GPIO_STATE_LOW);
    spi_transmittion_start(&request);
}

void
spi_on_response_received_isr(uint8_t response[])
{
    gpio_set_state(&attention, GPIO_STATE_HIGH);
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
        queue_message_t message = queue_message_create_command(command);
        queue_push(QUEUE_TOPIC_REMOTE_CONTROL, message);
    }
}