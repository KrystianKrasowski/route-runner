#include "gpio.h"
#include <stm32f3xx.h>
#include <string.h>

typedef struct gpio_definition
{
    uint32_t      rcc_gpioxen;
    GPIO_TypeDef *gpiox;
    uint8_t       bit;
} gpio_definition_t;

static gpio_definition_t gpio[9] = {
    [GPIO_DUALSHOCK2_ATTENTION] = {RCC_AHBENR_GPIOFEN, GPIOF, 0},
    [GPIO_MOTOR_LEFT_A1] = {RCC_AHBENR_GPIOAEN, GPIOA, 10},
    [GPIO_MOTOR_LEFT_A2] = {RCC_AHBENR_GPIOAEN, GPIOA, 12},
    [GPIO_MOTOR_RIGHT_A1] = {RCC_AHBENR_GPIOBEN, GPIOB, 7},
    [GPIO_MOTOR_RIGHT_A2] = {RCC_AHBENR_GPIOBEN, GPIOB, 6},
};

void
gpio_init(gpio_t *self)
{
    // init object
    self->mode  = GPIO_MODE_OUTPUT;
    self->state = GPIO_STATE_LOW;

    // init peripheral
    gpio_definition_t *definition = &gpio[self->pin];

    // This block reads RCC->AHBENR twice, but writes only when necessarry
    // Reading is faster than writing and this is still init phase
    if ((RCC->AHBENR & definition->rcc_gpioxen) == 0)
    {
        RCC->AHBENR |= definition->rcc_gpioxen;
    }

    // Get MODER bits by pin index. There is always MODER two bits for each GPIO
    uint32_t moderx_pos = definition->bit * 2;
    uint32_t moderx_0   = (1 << moderx_pos);
    uint32_t moderx_1   = (2 << moderx_pos);

    if (self->mode == GPIO_MODE_OUTPUT)
    {
        definition->gpiox->MODER |= moderx_0;
        definition->gpiox->MODER &= ~moderx_1;
    }
    else
    {
        definition->gpiox->MODER &= ~(moderx_0 | moderx_1);
    }
}

void
gpio_set_state(gpio_t *self, gpio_state_t const state)
{
    gpio_definition_t *definition = &gpio[self->pin];

    if (state == GPIO_STATE_LOW)
    {
        definition->gpiox->ODR &= ~(1 << definition->bit);
    }
    else
    {
        definition->gpiox->ODR |= (1 << definition->bit);
    }

    self->state = state;
}