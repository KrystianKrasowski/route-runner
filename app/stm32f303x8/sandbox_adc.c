#include <adc.h>
#include <usart2.h>
#include <stdio.h>

int
main(void)
{
    usart2_tx_init();
    printf("Waiting for readings...\n");
    adc_init();
    adc_on();
    adc_start();

    while (1)
    {
    }
}

__attribute__((weak)) void
adc_sequence_complete_isr(uint16_t volatile value[], uint8_t size)
{
    printf("V1: %d; V2: %d; V3: %d; V4: %d\n", value[0], value[1], value[2], value[3]);
}