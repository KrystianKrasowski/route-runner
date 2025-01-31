#include "tim3.h"
#include "stm32f3xx.h"

void
tim3_ch1_init(void)
{
    // set clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // set compare match every 1s on channel 1
    TIM3->PSC  = 8000 - 1;
    TIM3->ARR  = 1000 - 1;
    TIM3->CCR1 = 1000;

    // enable the timer
    TIM3->CR1 |= TIM_CR1_CEN;

    // enable capture/compare interrupt for channel 1
    TIM3->DIER |= TIM_DIER_CC1IE;

    // enable TIM3 IRQ in NVIC
    NVIC_EnableIRQ(TIM3_IRQn);
}

void
TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_CC1IF)
    {
        TIM3->SR &= ~TIM_SR_CC1IF;
        tim3_ch1_compare_isr();
    }
}

__attribute__((weak)) void
tim3_ch1_compare_isr(void)
{
}