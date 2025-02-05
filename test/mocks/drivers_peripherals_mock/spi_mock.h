#ifndef _SPI_MOCK_H
#define _SPI_MOCK_H

#include <spi.h>
#include <stdbool.h>
#include <stdint.h>

int
spi_mock_verify_init_master_calls(void);

bool
spi_mock_verify_transmission_start_request(uint8_t request[], uint8_t size);

void
spi_mock_reset(void);

#endif