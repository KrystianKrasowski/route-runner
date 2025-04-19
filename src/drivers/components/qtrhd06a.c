#include "qtrhd06a.h"
#include <adc.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <utils/result.h>

typedef struct
{
    uint16_t read_buffer[ADC_BUFFER_SIZE];
    bool volatile handled;
} qtrhd06a_payload_t;

#define COORDS_SIZE 6
#define NOT_READY   1

static qtrhd06a_payload_t payload;

void
qtrhd06a_init(void)
{
    memset(&payload, 0, sizeof(payload));
    payload.handled = true;

    adc_init();
    adc_on();
    adc_start();
}

void
adc_sequence_complete_isr(uint16_t const value[])
{
    if (payload.handled)
    {
        memcpy(&payload.read_buffer, value, sizeof(payload.read_buffer));
        payload.handled = false;
    }
}

int
qtrhd06a_read(uint8_t values[])
{
    int result = RESULT_OK;

    if (!payload.handled)
    {
        uint16_t l3 = 0;
        uint16_t l2 = 0;
        uint16_t l1 = 0;
        uint16_t r1 = 0;
        uint16_t r2 = 0;
        uint16_t r3 = 0;

        for (uint8_t i = 0; i < ADC_BUFFER_SIZE; i += 4)
        {
            r1 += (payload.read_buffer[i] >> 8) & 0xff;
            r3 += (payload.read_buffer[i]) & 0xff;
            l1 += (payload.read_buffer[i + 1] >> 8) & 0xff;
            r2 += (payload.read_buffer[i + 1]) & 0xff;
            l2 += (payload.read_buffer[i + 2] >> 8) & 0xff;
            l3 += (payload.read_buffer[i + 3] >> 8) & 0xff;
        }

        values[0] = l3 / 10;
        values[1] = l2 / 10;
        values[2] = l1 / 10;
        values[3] = r1 / 10;
        values[4] = r2 / 10;
        values[5] = r3 / 10;

        payload.handled = true;
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
}
