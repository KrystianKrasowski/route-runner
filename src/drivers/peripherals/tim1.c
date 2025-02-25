#include "tim1.h"
#include "sysclock.h"
#include <stm32f3xx.h>

static volatile uint8_t count = 0;

static uint8_t const half_interval   = 125;
static uint32_t volatile auto_reload = half_interval;
static uint8_t toggles                = 8;

static uint32_t
count_auto_reload(void);

void
tim1_ch1_init(void)
{
    // enable clock access to gpioa
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // set pa8 to alternate function mode
    GPIOA->MODER |= GPIO_MODER_MODER8_1;
    GPIOA->MODER &= ~GPIO_MODER_MODER8_0;

    // set alternafe function to AF6 (tim1_ch1)
    GPIOA->AFR[1] |= (6 << GPIO_AFRH_AFRH0_Pos);

    // enable clock access to tim1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // set compare match
    TIM1->PSC = sysclock_get_prescaller_base(1000) - 1;
    TIM1->ARR = 125 - 1;

    // set toggle on compare
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM1->CCMR1 |= (3 << TIM_CCMR1_OC1M_Pos);

    // enable output
    TIM1->CCER |= TIM_CCER_CC1E;

    // enable main output (necesary for TIM1)
    TIM1->BDTR |= TIM_BDTR_MOE;

    // enable the timer
    TIM1->CR1 |= TIM_CR1_CEN;

    // enable capture/compare interrupt for channel 1
    TIM1->DIER |= TIM_DIER_CC1IE;

    // enable TIM1 IRQ in NVIC
    NVIC_EnableIRQ(TIM1_CC_IRQn);
}

void
tim1_ch1_set_toggles(uint8_t count)
{
    count = count % 8;

    if (count == 0)
    {
        count = 8;
    }

    toggles = count;
}

void
TIM1_CC_IRQHandler(void)
{
    if (TIM1->SR & TIM_SR_CC1IF)
    {
        if (count == 0)
        {
            TIM1->ARR = 125 - 1;
        }

        count++;

        if (count >= toggles)
        {
            count     = 0;
            TIM1->ARR = count_auto_reload() - 1;
        }

        TIM1->SR &= ~TIM_SR_CC1IF;
    }
}

static uint32_t
count_auto_reload(void)
{
    return 1000 - toggles * half_interval + half_interval;
}