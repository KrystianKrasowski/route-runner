#include <assert.h>
#include <devices/dualshock2.h>
#include <devices/dualshock2_mock.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

#define PAYLOAD_MAX_LENGTH 9

typedef struct
{
    uint16_t buttons;
} dualshock2_mock_t;

POOL_DECLARE(dualshock2_mock,
             dualshock2_mock_t,
             DEVICE_DUALSHOCK2_INSTANCES_NUM)

static dualshock2_mock_pool_t pool;

void
device_dualshock2_mock_init(void)
{
    dualshock2_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_DUALSHOCK2_INSTANCES_NUM; i++)
    {
        dualshock2_mock_pool_alloc_at(&pool, i);
    }
}

void
device_dualshock2_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_DUALSHOCK2_INSTANCES_NUM; i++)
    {
        dualshock2_mock_pool_free(&pool, i);
    }
}

void
device_dualshock2_mock_set_buttons(device_dualshock2_t const h_self,
                                   uint16_t const            buttons)
{
    dualshock2_mock_t *p_self = dualshock2_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->buttons = buttons;
}

int
device_dualshock2_read(device_dualshock2_t const h_self, uint16_t *p_commands)
{
    dualshock2_mock_t *p_self = dualshock2_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    *p_commands = p_self->buttons;

    return RESULT_OK;
}
