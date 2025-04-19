#include "dualshock2.h"
#include <gpio.h>
#include <spi.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <tim2.h>
#include <utils/result.h>

#define DUALSHOCK2_RESPONSE_SIZE 9

typedef struct
{
    uint16_t last_command;
    bool volatile handled;
} dualshock2_payload_t;

static spi_request_t request = {
    .payload       = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .size          = 9,
    .device_select = {GPIO_DUALSHOCK2_ATTENTION},
};

static dualshock2_payload_t payload;

void
dualshock2_init(void)
{
    memset(&payload, 0, sizeof(payload));
    payload.last_command = DS2_NONE;
    payload.handled      = true;

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
spi_on_response_received_isr(uint8_t const response[])
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

    if (payload.handled && payload.last_command != command)
    {
        payload.last_command = command;
        payload.handled      = false;
    }
}

int
dualshock2_read(uint16_t *p_commands)
{
    int result = RESULT_OK;

    if (!payload.handled)
    {
        *p_commands     = payload.last_command;
        payload.handled = true;
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
}