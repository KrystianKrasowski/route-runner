#include "qtrhd06a.h"
#include <adc.h>
#include <mq.h>
#include <string.h>

#define COORDS_SIZE 6

void
qtrhd06a_init(void)
{
    adc_init();
    adc_on();
    adc_start();
}

/**
 * ADC sequence complete ISR
 * --------------------------
 * Performs lightweight averaging of 40 ADC samples into 6 8-bit values
 * and pushes the result to a circular message queue.
 *
 * Note: While this processing could be deferred to the main loop
 * to reduce ISR duration, it is done here to save RAM by avoiding
 * copying the full ADC buffer (~80 bytes) via message passing.
 *
 * This tradeoff is safe due to:
 *  - Simple integer-only processing
 *  - Short and deterministic execution time
 *  - ISR-safe, static, circular queue per topic
 *
 * If ISR timing becomes critical in the future, consider refactoring
 * to move processing into the main loop using a double buffer.
 */
void
adc_sequence_complete_isr(uint16_t const value[])
{
    uint16_t l3 = 0;
    uint16_t l2 = 0;
    uint16_t l1 = 0;
    uint16_t r1 = 0;
    uint16_t r2 = 0;
    uint16_t r3 = 0;

    for (uint8_t i = 0; i < ADC_BUFFER_SIZE; i += 4)
    {
        r1 += (value[i] >> 8) & 0xff;
        r3 += (value[i]) & 0xff;
        l1 += (value[i + 1] >> 8) & 0xff;
        r2 += (value[i + 1]) & 0xff;
        l2 += (value[i + 2] >> 8) & 0xff;
        l3 += (value[i + 3] >> 8) & 0xff;
    }

    uint8_t coords[COORDS_SIZE];
    coords[0] = l3 / 10;
    coords[1] = l2 / 10;
    coords[2] = l1 / 10;
    coords[3] = r1 / 10;
    coords[4] = r2 / 10;
    coords[5] = r3 / 10;

    mq_message_t message = mq_create_message(coords, sizeof(coords));
    mq_push(MQ_TOPIC_COORDS, &message);
}

void
qtrhd06a_parse_values(uint8_t const *byte_buffer, uint8_t *p_values)
{
    memcpy(p_values, byte_buffer, COORDS_SIZE);
}