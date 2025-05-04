#include "dualshock2.h"
#include "spi_transmittion.h"
#include <devices/dualshock2.h>
#include <errno.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>
#include <utils/volatile_string.h>

#define PAYLOAD_SIZE 9

typedef struct
{
    uint32_t         device_select_port;
    uint16_t         device_select_pin;
    uint32_t         spi_port;
    volatile uint8_t state[PAYLOAD_SIZE];
    volatile bool    handled;
} dualshock2_instance_t;

POOL_DECLARE(dualshock2, dualshock2_instance_t, 1)

static uint8_t PAYLOAD[PAYLOAD_SIZE] = {
    0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static dualshock2_pool_t pool;

static inline bool
state_is_valid(volatile uint8_t const response[]);

int
device_dualshock2_read(device_dualshock2_t const h_self, uint16_t *p_commands)
{
    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (p_self->handled)
    {
        return RESULT_NOT_READY;
    }

    if (state_is_valid(p_self->state))
    {
        *p_commands = ~(((uint16_t)p_self->state[4] << 8) | p_self->state[3]);
    }
    else
    {
        *p_commands = DS2_NONE;
    }

    p_self->handled = true;

    return RESULT_OK;
}

void
dualshock2_init(void)
{
    dualshock2_pool_init(&pool);
}

int
dualshock2_create(device_dualshock2_t const handle,
                  dualshock2_conf_t const  *p_conf)
{
    if (!dualshock2_pool_alloc_at(&pool, handle))
    {
        return -ENOMEM;
    }

    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, handle);

    p_self->device_select_port = p_conf->device_select_port;
    p_self->device_select_pin  = p_conf->device_select_pin;
    p_self->spi_port           = p_conf->spi_port;
    p_self->handled            = false;

    memset_volatile(p_self->state, 0, sizeof(p_self->state));

    gpio_set(p_self->device_select_port, p_self->device_select_pin);

    return RESULT_OK;
}

int
dualshock2_poll(device_dualshock2_t const h_self)
{
    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    spi_transmittion_conf_t conf = {
        .spi_port           = p_self->spi_port,
        .device_select_port = p_self->device_select_port,
        .device_select_pin  = p_self->device_select_pin,
    };

    spi_transmittion_start(SPI_TRANSMITTION_SPI1, &conf, PAYLOAD, PAYLOAD_SIZE);

    return RESULT_OK;
}

int
dualshock2_set_state(device_dualshock2_t const h_self, uint8_t const response[])
{
    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    memcpy_volatile(p_self->state, response, PAYLOAD_SIZE);

    p_self->handled = false;

    return RESULT_OK;
}

static inline bool
state_is_valid(volatile uint8_t const state[])
{
    bool b_1st_byte_valid = 0xff == state[0];
    bool b_2nd_byte_valid = 0x41 == state[1] || 0x73 == state[1];
    bool b_3rd_byte_valid = 0x5a == state[2];

    return b_1st_byte_valid && b_2nd_byte_valid && b_3rd_byte_valid;
}
