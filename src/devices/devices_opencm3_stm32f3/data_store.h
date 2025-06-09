/**
 * An experiment to use data oriented design
 */

#ifndef _DEVICES_OPENCM3_STM32F3_DATA_STORE_H
#define _DEVICES_OPENCM3_STM32F3_DATA_STORE_H

#include <stdbool.h>
#include <stdint.h>

#define DATA_STORE_ROUTE_BUFF_LENGTH      40
#define DATA_STORE_DUALSHOCK2_BUFF_LENGTH 5
#define DATA_STORE_SERIAL_TXBUFF_LENGTH   100

uint32_t
data_store_get_route_wbuff_addr(void);

void
data_store_update_route(void);

volatile uint16_t *
data_store_get_route_rbuff(void);

uint32_t
data_store_get_dualshock2_request_addr(void);

uint32_t
data_store_get_dualshock2_wbuff_addr(void);

void
data_store_update_dualshock2(void);

volatile uint8_t *
data_store_get_dualshock2_rbuff(void);

void
data_store_update_serial_request(char const request);

char
data_store_get_serial_request(void);

volatile char *
data_store_get_serial_txbuff(void);

uint32_t
data_store_get_serial_txbuff_addr(void);

void
data_store_clear_serial_txbuff(void);

#endif
