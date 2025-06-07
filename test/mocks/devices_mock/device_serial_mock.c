#include <assert.h>
#include <devices/serial_mock.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    char command;
    char message[DEVICE_SERIAL_MAX_LINE_LENGTH];
} serial_mock_t;

POOL_DECLARE(serial_mock, serial_mock_t, DEVICE_SERIAL_INSTANCES_NUM)

static serial_mock_pool_t pool;

int
device_serial_read(device_serial_t const h_self, char const command)
{
    serial_mock_t *p_self = serial_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    return p_self->command == command ? RESULT_OK : RESULT_NOT_READY;
}

int
device_serial_write(device_serial_t const h_self,
                    char const            message[],
                    uint8_t               length)
{
    serial_mock_t *p_self = serial_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    if (length > DEVICE_SERIAL_MAX_LINE_LENGTH)
    {
        length = DEVICE_SERIAL_MAX_LINE_LENGTH;
    }

    strcpy(p_self->message, message);

    return RESULT_OK;
}

void
device_serial_mock_init(void)
{
    serial_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_SERIAL_INSTANCES_NUM; i++)
    {
        serial_mock_pool_alloc_at(&pool, i);
    }
}

void
device_serial_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_SERIAL_INSTANCES_NUM; i++)
    {
        serial_mock_pool_free(&pool, i);
    }
}

void
device_serial_mock_set_requested(device_serial_t const h_device,
                                 char const            command)
{
    serial_mock_t *p_self = serial_mock_pool_get(&pool, h_device);

    assert(NULL != p_self);

    p_self->command = command;
}

char *
device_serial_mock_get_applied_msg(device_serial_t const h_device)
{
    serial_mock_t *p_self = serial_mock_pool_get(&pool, h_device);

    assert(NULL != p_self);

    return p_self->message;
}
