#include "spi_mock.h"
#include <spi.h>
#include <string.h>

static int     init_master_calls             = 0;
static uint8_t last_request[SPI_BUFFER_SIZE] = {0};

void
spi_init_master(void)
{
    init_master_calls++;
}

void
spi_transmittion_start(uint8_t const request[], uint8_t size)
{
    memcpy(&last_request, request, size);
}

int
spi_mock_verify_init_master_calls(void)
{
    return init_master_calls;
}

bool
spi_mock_verify_transmission_start_request(uint8_t request[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        if (last_request[i] != request[i])
        {
            return false;
        }
    }

    return true;
}

void
spi_mock_reset(void)
{
    init_master_calls = 0;
    memset(&last_request, 0, SPI_BUFFER_SIZE);
}