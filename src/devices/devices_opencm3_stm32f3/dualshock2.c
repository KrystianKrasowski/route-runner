#include "data_store.h"
#include "dualshock2.h"
#include "notification.h"
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

// cppcheck-suppress unusedFunction
POOL_DECLARE(dualshock2, dualshock2_instance_t, 1)

static uint8_t PAYLOAD[PAYLOAD_SIZE] = {
    0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static dualshock2_pool_t pool;

static inline bool
state_is_valid(volatile uint8_t const state[]);

int
device_dualshock2_read(device_dualshock2_t const h_self, uint16_t *p_commands)
{
    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (!notification_take(NOTIFICATION_DUALSHOCK2))
    {
        return RESULT_NOT_READY;
    }

    volatile uint8_t *state = data_store_get_dualshock2_rbuff();

    if (state_is_valid(state))
    {
        *p_commands = ~(((uint16_t)state[4] << 8) | state[3]);
    }
    else
    {
        *p_commands = DS2_NONE;
    }

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

    gpio_set(p_self->device_select_port, p_self->device_select_pin);

    return RESULT_OK;
}

int
dualshock2_poll_start(device_dualshock2_t const h_self)
{
    dualshock2_instance_t const *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    spi_enable_tx_dma(p_self->spi_port);
    spi_enable_rx_dma(p_self->spi_port);
    spi_enable(p_self->spi_port);
    gpio_clear(p_self->device_select_port, p_self->device_select_pin);

    return RESULT_OK;
}

int
dualshock2_poll_end(device_dualshock2_t const h_self)
{
    dualshock2_instance_t const *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    spi_disable(p_self->spi_port);
    spi_disable_tx_dma(p_self->spi_port);
    spi_disable_rx_dma(p_self->spi_port);
    gpio_set(p_self->device_select_port, p_self->device_select_pin);

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
