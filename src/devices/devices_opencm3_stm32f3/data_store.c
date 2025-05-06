#include "data_store.h"
#include <utils/volatile_string.h>

typedef struct
{
    volatile uint16_t route_write_buffer[DATA_STORE_ROUTE_BUFFER_LENGTH];
    volatile uint16_t route_read_buffer[DATA_STORE_ROUTE_BUFFER_LENGTH];
    volatile bool     route_handled;
} data_store_t;

static data_store_t store;

uint32_t
data_store_get_route_write_buffer_addr(void)
{
    return (uint32_t)store.route_write_buffer;
}

void
data_store_receive_adc_route(void)
{
    memcpy_volatile(&store.route_read_buffer,
                    &store.route_write_buffer,
                    sizeof(store.route_read_buffer));

    store.route_handled = false;
}

volatile uint16_t *
data_store_get_route_read_buffer(void)
{
    return store.route_read_buffer;
}

volatile bool *
data_store_get_route_handled_flag(void)
{
    return &store.route_handled;
}
