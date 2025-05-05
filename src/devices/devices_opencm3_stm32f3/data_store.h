/**
 * An experiment to use data oriented design
 */

#ifndef _DEVICES_OPENCM3_STM32F3_DATA_STORE_H
#define _DEVICES_OPENCM3_STM32F3_DATA_STORE_H

#include <stdbool.h>
#include <stdint.h>

#define DATA_STORE_ROUTE_BUFFER_LENGTH 40

// TODO: Consider opaque handle here
typedef struct
{
    volatile uint16_t route_write_buffer[DATA_STORE_ROUTE_BUFFER_LENGTH];
    volatile uint16_t route_read_buffer[DATA_STORE_ROUTE_BUFFER_LENGTH];
    volatile bool     route_handled;
} data_store_t;

uint32_t
data_store_get_route_write_buffer_addr(void);

void
data_store_receive_adc_route(void);

volatile uint16_t *
data_store_get_route_read_buffer(void);

volatile bool *
data_store_get_route_handled_flag(void);

#endif
