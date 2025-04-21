#include "l293.h"
#include "sysclock.h"
#include <drivers/l293.h>
#include <errno.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef enum
{
    L293_PWM_CHANNEL_3,
    L293_PWM_CHANNEL_4,
} l293_pwm_channel_t;

typedef struct
{
    GPIO_TypeDef *port;
    uint8_t       bit;
} l293_gpio_t;

typedef struct
{
    l293_gpio_t        gpio_1;
    l293_gpio_t        gpio_2;
    l293_pwm_channel_t pwm;
} l293_instance_t;

// cppcheck-suppress unusedFunction
POOL_DECLARE(l293, l293_instance_t, 2)

static l293_pool_t pool;

static inline void
init_gpio(void);

static inline void
init_pwm(void);

static inline void
create_instance_12(void);

static inline void
create_instance_34(void);

void
l293_init(void)
{
    init_gpio();
    init_pwm();
    l293_pool_init(&pool);
    create_instance_12();
    create_instance_34();
}

int
l293_set_left(l293_t h_self)
{
    l293_instance_t *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    p_self->gpio_1.port->ODR |= (1 << p_self->gpio_1.bit);
    p_self->gpio_2.port->ODR &= ~(1 << p_self->gpio_2.bit);

    return RESULT_OK;
}

int
l293_set_right(l293_t h_self)
{
    l293_instance_t *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    p_self->gpio_1.port->ODR &= ~(1 << p_self->gpio_1.bit);
    p_self->gpio_2.port->ODR |= (1 << p_self->gpio_2.bit);

    return RESULT_OK;
}

int
l293_set_stop(l293_t h_self)
{
    l293_instance_t *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    p_self->gpio_1.port->ODR &= ~(1 << p_self->gpio_1.bit);
    p_self->gpio_2.port->ODR &= ~(1 << p_self->gpio_2.bit);

    return RESULT_OK;
}

int
l293_enable(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    switch (p_self->pwm)
    {
        case L293_PWM_CHANNEL_3:
            TIM3->CCER |= TIM_CCER_CC3E;
            break;
        case L293_PWM_CHANNEL_4:
            TIM3->CCER |= TIM_CCER_CC4E;
            break;
        default:
            return -EINVAL;
    }

    return RESULT_OK;
}

int
l293_disable(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    switch (p_self->pwm)
    {
        case L293_PWM_CHANNEL_3:
            TIM3->CCER &= ~TIM_CCER_CC3E;
            break;
        case L293_PWM_CHANNEL_4:
            TIM3->CCER &= ~TIM_CCER_CC4E;
            break;
        default:
            return -EINVAL;
    }

    return RESULT_OK;
}

static inline void
init_gpio(void)
{
    // enable clock access to GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // enable clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Set PA12 as output - L293 control input 1A
    GPIOA->MODER |= GPIO_MODER_MODER12_0;
    GPIOA->MODER &= ~GPIO_MODER_MODER12_1;

    // Set PA10 as output - L293 control input 2A
    GPIOA->MODER |= GPIO_MODER_MODER10_0;
    GPIOA->MODER &= ~GPIO_MODER_MODER10_1;

    // Set PB6 as output - L293 control input 3A
    GPIOB->MODER |= GPIO_MODER_MODER6_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER6_1;

    // Set PB7 as output - L293 control input 4A
    GPIOB->MODER |= GPIO_MODER_MODER7_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER7_1;

    // set PB0 in alternate function mode
    GPIOB->MODER &= ~GPIO_MODER_MODER0_0;
    GPIOB->MODER |= GPIO_MODER_MODER0_1;

    // set AF2 (TIM3_CH3) for PB0 - L293 enable input 12EN
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL0_Pos);

    // set PB1 in alternate function mode
    GPIOB->MODER &= ~GPIO_MODER_MODER1_0;
    GPIOB->MODER |= GPIO_MODER_MODER1_1;

    // set AF2 (TIM3_CH4) for PB1 - L293 enable input 34EN
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL1_Pos);
}

static inline void
init_pwm(void)
{
    // enable clock access to TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // set prescaler value for 10kHz TIMER frequency
    TIM3->PSC = sysclock_get_prescaller_base(1000000) - 1;
    TIM3->ARR = 100 - 1;

    // set center aligned mode resulting 5kHz PWM frequency
    TIM3->CR1 |= TIM_CR1_CMS_0;

    // Force update event to load ARR, PSC, and PWM settings
    TIM3->EGR |= TIM_EGR_UG;

    // default duty cycle to 90% for channel 3
    TIM3->CCR3 = 90;

    // default duty cycle to 90% for channel 4
    TIM3->CCR4 = 90;

    // set PWM mode for channel 3
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;

    // set PWM mode for channel 4
    TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;

    // set preload enable for channel 3
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;

    // set preload enable for channel 4
    TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
}

static inline void
create_instance_12(void)
{
    l293_pool_alloc_at(&pool, L293_CHANNEL_12);

    l293_instance_t *p_self = l293_pool_get(&pool, L293_CHANNEL_12);

    l293_gpio_t gpio_1 = {.port = GPIOA, .bit = 12};
    l293_gpio_t gpio_2 = {.port = GPIOA, .bit = 10};

    p_self->gpio_1 = gpio_1;
    p_self->gpio_2 = gpio_2;
    p_self->pwm    = L293_PWM_CHANNEL_3;
}

static inline void
create_instance_34(void)
{
    l293_pool_alloc_at(&pool, L293_CHANNEL_12);

    l293_instance_t *p_self = l293_pool_get(&pool, L293_CHANNEL_12);

    l293_gpio_t gpio_1 = {.port = GPIOB, .bit = 6};
    l293_gpio_t gpio_2 = {.port = GPIOB, .bit = 7};

    p_self->gpio_1 = gpio_1;
    p_self->gpio_2 = gpio_2;
    p_self->pwm    = L293_PWM_CHANNEL_4;
}