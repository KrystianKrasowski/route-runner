#include "data_store.h"
#include <utils/volatile_string.h>

static data_store_t store;

uint32_t
data_store_get_adc_route_write_buffer_addr(void)
{
    return (uint32_t)(uintptr_t)&store.adc_route_write_buffer;
}

void
data_store_receive_adc_route(void)
{
    memcpy_volatile(&store.adc_route_read_buffer,
                    &store.adc_route_write_buffer,
                    sizeof(store.adc_route_read_buffer));

    store.adc_route_handled = false;
}
