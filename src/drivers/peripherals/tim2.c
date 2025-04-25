#include "tim2.h"
#include "sysclock.h"
#include <stm32f3xx.h>

void
tim2_ch1_init(void)
{
    // set clock access to TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // set compare match every 16ms on channel 1
    TIM2->PSC  = sysclock_get_prescaller_base(1000) - 1;
    TIM2->ARR  = 16 - 1;
    TIM2->CCR1 = 16;

    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->DIER |= TIM_DIER_UIE;

    // enable the timer
    TIM2->CR1 |= TIM_CR1_CEN;

    // enable TIM2 IRQ in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);
}

void
// cppcheck-suppress unusedFunction
TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        tim2_ch1_compare_isr();
    }
}

__attribute__((weak)) void
tim2_ch1_compare_isr(void)
{
}