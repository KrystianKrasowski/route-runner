#include <adc.h>
#include <stm32f3xx.h>
#include <sysclock.h>
#include <usart2.h>
#include <stdio.h>

uint16_t volatile v1 = 0;
uint16_t volatile v2 = 0;
uint16_t volatile v3 = 0;

int
main(void)
{
    sysclock_init();

    usart2_tx_init();
    printf("Waiting for readings...\n");
    adc_init();
    adc_on();
    adc_start();

    while (1)
    {
        printf("V1: %d; V2: %d; V3: %d\n", v1, v2, v3);
    }
}

void
adc_sequence_complete_isr(uint16_t volatile value[])
{
    v1 = value[0];
    v2 = value[1];
    v3 = value[2];
    // printf("V1: %d; V2: %d; V3: %d\n", v1, v2, v3);
}