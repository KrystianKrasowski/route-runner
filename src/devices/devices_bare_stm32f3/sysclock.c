#include "sysclock.h"
#include <stm32f3xx.h>

void
sysclock_init(void)
{
    // According to default settings this will set system clock to 16MHz
    // HPRE: default 0 - no prescaller
    // PLLSRC: default 0 - HSI/2 - meaning 4MHZ
    // PLLMUL set to 2, that multiplies source by 4 - giving 16 MHz
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    RCC->CFGR |= (2 << RCC_CFGR_PLLMUL_Pos);

    // Set PLL on
    RCC->CR |= RCC_CR_PLLON;

    // wait for PLL to enable
    while (!(RCC->CR & RCC_CR_PLLRDY));
}

uint32_t
sysclock_get_prescaller_base(uint32_t resolution)
{
    return SYSCLOCK_FREQ / resolution;
}