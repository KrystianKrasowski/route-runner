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
adc_sequence_complete_isr(uint32_t value[])
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
            r1 += (uint16_t)(value[i] >> 16);
            r3 += (uint16_t)value[i];
        }
        else if (i % 4 == 1)
        {
            l1 += (uint16_t)(value[i] >> 16);
            r2 += (uint16_t)value[i];
        }
        else if (i % 4 == 2)
        {
            l2 += (uint16_t)(value[i] >> 16);
        }
        else
        {
            l3 += (uint16_t)(value[i] >> 16);
        }
    }

    uint8_t line_position[6];
    line_position[0] = l3 / 10;
    line_position[1] = l2 / 10;
    line_position[2] = l1 / 10;
    line_position[3] = r1 / 10;
    line_position[4] = r2 / 10;
    line_position[5] = r3 / 10;

    mq_message_t message = mq_create_position_message(line_position);
    mq_push(MQ_TOPIC_LINE_POSITION, message);
}