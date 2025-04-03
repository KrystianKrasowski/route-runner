#include "tim6.h"
#include "sysclock.h"
#include <stm32f3xx.h>

void
tim6_init(void)
{
    // set clock access to TIM6
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    // set frequency to 1MHz
    TIM6->PSC = sysclock_get_prescaller_base(1000000) - 1;

    // update event every 1ms
    TIM6->ARR = 1000 - 1;

    // enable TRGO on update event
    TIM6->CR2 |= (2 << TIM_CR2_MMS_Pos);
}

void
tim6_run(void)
{
    TIM6->CR1 |= TIM_CR1_CEN;
}

void
tim6_stop(void)
{
    TIM6->CR1 &= ~TIM_CR1_CEN;
}