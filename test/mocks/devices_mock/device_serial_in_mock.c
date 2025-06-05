#include <assert.h>
#include <devices/serial_in_mock.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    char command[2];
} serial_in_mock_t;

POOL_DECLARE(serial_in_mock, serial_in_mock_t, DEVICE_SERIAL_IN_INSTANCES_NUM)

static serial_in_mock_pool_t pool;

int
device_serial_in_read(device_serial_in_t const h_self, char *command)
{
    serial_in_mock_t *p_self = serial_in_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    int compare = memcmp(p_self->command, command, sizeof(p_self->command));

    return compare == 0 ? RESULT_OK : RESULT_NOT_READY;
}

void
device_serial_in_mock_init(void)
{
    serial_in_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_SERIAL_IN_INSTANCES_NUM; i++)
    {
        serial_in_mock_pool_alloc_at(&pool, i);
    }
}

void
device_serial_in_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_SERIAL_IN_INSTANCES_NUM; i++)
    {
        serial_in_mock_pool_free(&pool, i);
    }
}

void
device_serial_in_mock_set_requested(device_serial_in_t const h_device,
                                    char                    *command)
{
    serial_in_mock_t *p_self = serial_in_mock_pool_get(&pool, h_device);

    assert(NULL != p_self);

    memcpy(p_self->command, command, sizeof(p_self->command));
}
