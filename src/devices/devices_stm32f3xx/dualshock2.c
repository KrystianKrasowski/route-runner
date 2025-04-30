#include "dualshock2.h"
#include "gpio.h"
#include "interrupts.h"
#include "spi.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

#define PAYLOAD_SIZE 9

typedef struct
{
    gpio_t  device_select;
    spi_t   spi_bus;
    uint8_t state[PAYLOAD_SIZE];
    bool volatile handled;
} dualshock2_instance_t;

POOL_DECLARE(dualshock2, dualshock2_instance_t, DEVICE_DUALSHOCK2_INSTANCES_NUM)

static uint8_t PAYLOAD[PAYLOAD_SIZE] = {
    0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static dualshock2_pool_t pool;

static inline bool
state_is_valid(uint8_t const response[]);

void
dualshock2_init(void)
{
    dualshock2_pool_init(&pool);
}

void
dualshock2_create(device_dualshock2_t handle, dualshock2_conf_t *p_conf)
{
    dualshock2_pool_alloc_at(&pool, handle);

    dualshock2_instance_t *p_dualshock = dualshock2_pool_get(&pool, handle);

    p_dualshock->device_select = p_conf->device_select;
    p_dualshock->spi_bus       = p_conf->spi_bus;
    p_dualshock->handled       = false;

    memset(&p_dualshock->state, 0, sizeof(p_dualshock->state));

    gpio_set_state(p_dualshock->device_select, PERIPH_GPIO_STATE_HIGH);
}

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
tim2_on_update_isr(void)
{
    // explicit handle is assumed by the TIM2 indication
    dualshock2_instance_t *p_self =
        dualshock2_pool_get(&pool, DEVICE_DUALSHOCK2_1);

    if (NULL == p_self)
    {
        return;
    }

    spi_transmit(p_self->spi_bus, PAYLOAD, PAYLOAD_SIZE, p_self->device_select);
}

void
spi1_on_response_isr(uint8_t const response[])
{
    // explicit handle is assumed by the SPI1 indication
    dualshock2_instance_t *p_self =
        dualshock2_pool_get(&pool, DEVICE_DUALSHOCK2_1);

    if (NULL == p_self)
    {
        return;
    }

    if (memcmp(p_self->state, response, sizeof(p_self->state)) != 0)
    {
        memcpy(p_self->state, response, sizeof(p_self->state));
        p_self->handled = false;
    }
}

static inline bool
state_is_valid(uint8_t const state[])
{
    bool b_1st_byte_valid = 0xff == state[0];
    bool b_2nd_byte_valid = 0x41 == state[1] || 0x73 == state[1];
    bool b_3rd_byte_valid = 0x5a == state[2];

    return b_1st_byte_valid && b_2nd_byte_valid && b_3rd_byte_valid;
}
