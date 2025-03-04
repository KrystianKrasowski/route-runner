#include "qtrhd06a.h"
#include <adc.h>
#include <queue.h>
#include <string.h>

void
qtrhd06a_init(void)
{
    adc_init();
    adc_on();
    adc_start();
}

void
adc_sequence_complete_isr(uint8_t value[])
{
    uint16_t left   = 0;
    uint16_t middle = 0;
    uint16_t right  = 0;

    for (uint8_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        if (i % 3 == 0)
        {
            right += value[i];
        }
        else if (i % 3 == 1)
        {
            middle += value[i];
        }
        else
        {
            left += value[i];
        }
    }

    uint8_t line_position[3];
    line_position[0] = left / 10;
    line_position[1] = middle / 10;
    line_position[2] = right / 10;

    queue_message_t message = queue_message_create_line_position(line_position);
    queue_push(QUEUE_TOPIC_LINE_POSITION, message);
}