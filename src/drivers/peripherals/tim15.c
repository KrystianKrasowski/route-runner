#include "tim15.h"
#include "sysclock.h"
#include <stm32f3xx.h>

static bool volatile timeout = false;

void
tim15_init()
{
    // set clock access to TIM15
    RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;

    // set timer frequency to 1kHz
    TIM15->PSC = sysclock_get_prescaller_base(1000) - 1;

    // set update event to 500ms
    TIM15->ARR = 500 - 1;

    // reinitialize the counter and generates an update of the registers.
    // prevents from triggering the interrupt on timer enable!
    TIM15->EGR |= TIM_EGR_UG;

    // clear status register from update event interrupt flag
    TIM15->SR &= ~TIM_SR_UIF;

    // enable update event interrupts
    TIM15->DIER |= TIM_DIER_UIE;

    // enable TIM15 IRQ in NVIC
    NVIC_EnableIRQ(TIM15_IRQn);
}

void
tim15_start()
{
    TIM15->CR1 |= TIM_CR1_CEN;

    timeout = false;
}

void
tim15_stop()
{
    TIM15->CR1 &= ~TIM_CR1_CEN;
    TIM15->CNT = 0;

    timeout = false;
}

bool
tim15_is_timeout(void)
{
    return timeout;
}

void
// cppcheck-suppress unusedFunction
TIM15_IRQHandler(void)
{
    if (TIM15->SR & TIM_SR_UIF)
    {
        TIM15->SR &= ~TIM_SR_UIF;

        timeout = true;
    }
}