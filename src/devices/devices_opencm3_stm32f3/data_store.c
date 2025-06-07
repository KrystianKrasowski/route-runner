#include "data_store.h"
#include <stdint.h>
#include <utils/volatile_string.h>

typedef struct
{
    volatile uint16_t route_wbuff[DATA_STORE_ROUTE_BUFF_LENGTH];
    volatile uint16_t route_rbuff[DATA_STORE_ROUTE_BUFF_LENGTH];
    uint8_t           dualshock2_request[DATA_STORE_DUALSHOCK2_BUFF_LENGTH];
    volatile uint8_t  dualshock2_wbuff[DATA_STORE_DUALSHOCK2_BUFF_LENGTH];
    volatile uint8_t  dualshock2_rbuff[DATA_STORE_DUALSHOCK2_BUFF_LENGTH];
    volatile char     serial_request;
} data_store_t;

static data_store_t store = {
    .dualshock2_request = {0x1, 0x42, 0x0, 0x0, 0x0},
};

uint32_t
data_store_get_route_wbuff_addr(void)
{
    return (uint32_t)store.route_wbuff;
}

void
data_store_update_route(void)
{
    size_t size = sizeof(store.route_rbuff);
    memcpy_volatile(&store.route_rbuff, &store.route_wbuff, size);
}

volatile uint16_t *
data_store_get_route_rbuff(void)
{
    return store.route_rbuff;
}

uint32_t
data_store_get_dualshock2_request_addr(void)
{
    return (uint32_t)store.dualshock2_request;
}

uint32_t
data_store_get_dualshock2_wbuff_addr(void)
{
    return (uint32_t)store.dualshock2_wbuff;
}

void
data_store_update_dualshock2(void)
{
    size_t size = sizeof(store.dualshock2_rbuff);
    memcpy_volatile(&store.dualshock2_rbuff, &store.dualshock2_wbuff, size);
}

volatile uint8_t *
data_store_get_dualshock2_rbuff(void)
{
    return store.dualshock2_rbuff;
}

void
data_store_update_serial_request(char const request)
{
    store.serial_request = request;
}

char
data_store_get_serial_request(void)
{
    return store.serial_request;
}
