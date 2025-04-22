#include "gpio.h"
#include <errno.h>
#include <stdint.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

#define GPIO_USAGE_SIZE 17

typedef struct
{
    GPIO_TypeDef *GPIOx;
    uint8_t       bit;
} gpio_instance_t;

POOL_DECLARE(gpio, gpio_instance_t, GPIO_USAGE_SIZE)

static gpio_pool_t pool;

static inline void
init_rcc(void);

static inline void
create_all_instances(void);

static inline GPIO_TypeDef *
match_gpio_port(gpio_t h_gpio);

static inline uint8_t
match_gpio_bit(gpio_t h_gpio);

void
gpio_init(void)
{
    init_rcc();
    gpio_pool_init(&pool);
    create_all_instances();
}

int
gpio_set_mode(gpio_t h_self, gpio_mode_t mode)
{
    gpio_instance_t *p_self = gpio_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    // Get MODER bits by pin index. There is always two bits for MODER register
    uint32_t moderx_pos = p_self->bit * 2;
    uint32_t moderx_0   = (1 << moderx_pos);
    uint32_t moderx_1   = (2 << moderx_pos);

    switch (mode)
    {
        case PERIPH_GPIO_MODE_OUTPUT:
            p_self->GPIOx->MODER |= moderx_0;
            p_self->GPIOx->MODER &= ~moderx_1;
            break;

        case PERIPH_GPIO_MODE_ALTERNATE:
            p_self->GPIOx->MODER &= ~moderx_0;
            p_self->GPIOx->MODER |= moderx_1;
            break;

        case PERIPH_GPIO_MODE_ANALOG:
        default:
            p_self->GPIOx->MODER |= moderx_0 | moderx_1;
    }

    return RESULT_OK;
}

int
gpio_set_state(gpio_t h_self, gpio_state_t state)
{
    gpio_instance_t *p_self = gpio_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (PERIPH_GPIO_STATE_LOW == state)
    {
        p_self->GPIOx->ODR &= ~(1 << p_self->bit);
    }
    else
    {
        p_self->GPIOx->ODR |= (1 << p_self->bit);
    }

    return RESULT_OK;
}

int
gpio_set_alternate_func(gpio_t h_self, gpio_function_t function)
{
    gpio_instance_t *p_self = gpio_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    // STM32F303 keeps alternate function bits in two elements array, 8+ are at
    // higher index
    uint8_t afr_index = (p_self->bit < 8) ? 0 : 1;

    // higher bits (from 8) are counted from 0 again, there are always 4 bits
    // for AFR register
    uint32_t afr_pos = (p_self->bit % 8) * 4;

    p_self->GPIOx->AFR[afr_index] |= (function << afr_pos);

    return RESULT_OK;
}

static inline void
init_rcc(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
}

static inline void
create_all_instances(void)
{
    for (gpio_t h_gpio = 0; h_gpio < GPIO_USAGE_SIZE; h_gpio++)
    {
        if (gpio_pool_alloc(&pool, &h_gpio))
        {
            gpio_instance_t *p_gpio = gpio_pool_get(&pool, h_gpio);

            p_gpio->GPIOx = match_gpio_port(h_gpio);
            p_gpio->bit   = match_gpio_bit(h_gpio);
        }
    }
}

static inline GPIO_TypeDef *
match_gpio_port(gpio_t h_gpio)
{
    switch (h_gpio)
    {
        case PERIPH_GPIO_PA1:
        case PERIPH_GPIO_PA3:
        case PERIPH_GPIO_PA4:
        case PERIPH_GPIO_PA5:
        case PERIPH_GPIO_PA6:
        case PERIPH_GPIO_PA7:
        case PERIPH_GPIO_PA8:
        case PERIPH_GPIO_PA10:
        case PERIPH_GPIO_PA12:
            return GPIOA;

        case PERIPH_GPIO_PB0:
        case PERIPH_GPIO_PB1:
        case PERIPH_GPIO_PB3:
        case PERIPH_GPIO_PB4:
        case PERIPH_GPIO_PB5:
        case PERIPH_GPIO_PB6:
        case PERIPH_GPIO_PB7:
            return GPIOB;

        case PERIPH_GPIO_PF0:
            return GPIOF;
    }
}

static inline uint8_t
match_gpio_bit(gpio_t h_gpio)
{
    switch (h_gpio)
    {
        case PERIPH_GPIO_PA1:
        case PERIPH_GPIO_PB1:
            return 1;

        case PERIPH_GPIO_PA3:
        case PERIPH_GPIO_PB3:
            return 3;

        case PERIPH_GPIO_PA4:
        case PERIPH_GPIO_PB4:
            return 4;

        case PERIPH_GPIO_PA5:
        case PERIPH_GPIO_PB5:
            return 5;

        case PERIPH_GPIO_PA6:
        case PERIPH_GPIO_PB6:
            return 6;

        case PERIPH_GPIO_PA7:
        case PERIPH_GPIO_PB7:
            return 7;

        case PERIPH_GPIO_PA8:
            return 8;

        case PERIPH_GPIO_PA10:
            return 10;

        case PERIPH_GPIO_PA12:
            return 12;

        case PERIPH_GPIO_PB0:
        case PERIPH_GPIO_PF0:
            return 0;
    }
}