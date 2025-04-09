#include "qtrhd06a.h"
#include <adc.h>
#include <mq.h>
#include <string.h>

void
qtrhd06a_init(void)
{
    adc_init();
    adc_on();
    adc_start();
}

void
adc_sequence_complete_isr(uint16_t value[])
{
    uint16_t l3 = 0;
    uint16_t l2 = 0;
    uint16_t l1 = 0;
    uint16_t r1 = 0;
    uint16_t r2 = 0;
    uint16_t r3 = 0;

    for (uint8_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        if (i % 4 == 0)
        {
            r1 += (value[i] >> 8) & 0xff;
            r3 += value[i] & 0xff;
        }
        else if (i % 4 == 1)
        {
            l1 += (value[i] >> 8) & 0xff;
            r2 += value[i] & 0xff;
        }
        else if (i % 4 == 2)
        {
            l2 += (value[i] >> 8) & 0xff;
        }
        else
        {
            l3 += (value[i] >> 8) & 0xff;
        }
    }

    uint8_t coords[6];
    coords[0] = l3 / 10;
    coords[1] = l2 / 10;
    coords[2] = l1 / 10;
    coords[3] = r1 / 10;
    coords[4] = r2 / 10;
    coords[5] = r3 / 10;

    mq_message_t message = mq_create_coords_message(coords);
    mq_push(MQ_TOPIC_COORDS, &message);
}