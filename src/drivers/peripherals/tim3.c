#include "tim3.h"
#include <stm32f3xx.h>

#define PWM_CENTER_ALIGNED_MODE_1 1

static inline void
tim3_ch3_pwm_init(tim3_pwm_t *self);

static inline void
tim3_ch4_pwm_init(tim3_pwm_t *self);

static inline void
tim3_ch3_pwm_run(void);

static inline void
tim3_ch3_pwm_stop(void);

static inline void
tim3_ch4_pwm_run(void);

static inline void
tim3_ch4_pwm_stop(void);

static inline uint8_t
trim_duty_cycle(uint8_t percentage);

void
tim3_init(void)
{
    // enable clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // set prescaler value for 10kHz TIMER frequency
    TIM3->PSC = 8 - 1;
    TIM3->ARR = 100 - 1;

    // set center aligned mode resulting 5kHz PWM frequency
    TIM3->CR1 |= TIM_CR1_CMS_0;

    // Force update event to load ARR, PSC, and PWM settings
    TIM3->EGR |= TIM_EGR_UG;
}

void
tim3_enable(void)
{
    TIM3->CR1 |= TIM_CR1_CEN;
}

void
tim3_pwm_init(tim3_pwm_t *self)
{
    if (self->channel == TIM3_CHANNEL_3)
    {
        tim3_ch3_pwm_init(self);
    }

    if (self->channel == TIM3_CHANNEL_4)
    {
        tim3_ch4_pwm_init(self);
    }
}

void
tim3_pwm_run(tim3_pwm_t *self)
{
    if (self->channel == TIM3_CHANNEL_3)
    {
        tim3_ch3_pwm_run();
    }

    if (self->channel == TIM3_CHANNEL_4)
    {
        tim3_ch4_pwm_run();
    }
}

void
tim3_pwm_stop(tim3_pwm_t *self)
{
    if (self->channel == TIM3_CHANNEL_3)
    {
        tim3_ch3_pwm_stop();
    }

    if (self->channel == TIM3_CHANNEL_4)
    {
        tim3_ch4_pwm_stop();
    }
}

void
tim3_pwm_set_duty_cycle(tim3_pwm_t *self, uint8_t duty_cycle)
{
    if (self->channel == TIM3_CHANNEL_3)
    {
        TIM3->CCR3 = trim_duty_cycle(duty_cycle);
    }

    if (self->channel == TIM3_CHANNEL_4)
    {
        TIM3->CCR4 = trim_duty_cycle(duty_cycle);
    }
}

static inline void
tim3_ch3_pwm_init(tim3_pwm_t *self)
{
    // enable clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // set PB0 in alternate function mode
    GPIOB->MODER &= ~GPIO_MODER_MODER0_0;
    GPIOB->MODER |= GPIO_MODER_MODER0_1;

    // set AF6 for PB0
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL0_Pos);

    // default duty cycle to 90%
    TIM3->CCR3 = trim_duty_cycle(self->duty_cycle);

    // set PWM mode
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;

    // set preload enable
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;
}

static inline void
tim3_ch4_pwm_init(tim3_pwm_t *self)
{
    // enable clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // set PB1 in alternate function mode
    GPIOB->MODER &= ~GPIO_MODER_MODER1_0;
    GPIOB->MODER |= GPIO_MODER_MODER1_1;

    // set AF6 for PB1
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL1_Pos);

    // default duty cycle to 90%
    TIM3->CCR4 = trim_duty_cycle(self->duty_cycle);

    // set PWM mode
    TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;

    // set preload enable
    TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
}

static inline void
tim3_ch3_pwm_run(void)
{
    // Enable the output channel
    TIM3->CCER |= TIM_CCER_CC3E;
}

static inline void
tim3_ch3_pwm_stop(void)
{
    // Disable the output channel
    TIM3->CCER &= ~TIM_CCER_CC3E;
}

static inline void
tim3_ch4_pwm_run(void)
{
    // Enable the output channel
    TIM3->CCER |= TIM_CCER_CC4E;
}

static inline void
tim3_ch4_pwm_stop(void)
{
    // Disable the output channel
    TIM3->CCER &= ~TIM_CCER_CC4E;
}

static inline uint8_t
trim_duty_cycle(uint8_t percentage)
{
    if (percentage >= 100)
    {
        return 100;
    }
    
    return percentage;
}