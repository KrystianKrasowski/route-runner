#ifndef _DEVICES_STM32F303XX_GPIO_H
#define _DEVICES_STM32F303XX_GPIO_H

typedef enum
{
    PERIPH_GPIO_PA1,
    PERIPH_GPIO_PA3,
    PERIPH_GPIO_PA4,
    PERIPH_GPIO_PA5,
    PERIPH_GPIO_PA6,
    PERIPH_GPIO_PA7,
    PERIPH_GPIO_PA8,
    PERIPH_GPIO_PA10,
    PERIPH_GPIO_PA12,
    PERIPH_GPIO_PB0,
    PERIPH_GPIO_PB1,
    PERIPH_GPIO_PB3,
    PERIPH_GPIO_PB4,
    PERIPH_GPIO_PB5,
    PERIPH_GPIO_PB6,
    PERIPH_GPIO_PB7,
    PERIPH_GPIO_PF0,
} gpio_t;

typedef enum
{
    PERIPH_GPIO_MODE_ANALOG,
    PERIPH_GPIO_MODE_OUTPUT,
    PERIPH_GPIO_MODE_ALTERNATE,
} gpio_mode_t;

typedef enum
{
    PERIPH_GPIO_STATE_LOW,
    PERIPH_GPIO_STATE_HIGH,
} gpio_state_t;

typedef enum
{
    PERIPH_GPIO_AF2 = 2,
    PERIPH_GPIO_AF5 = 5,
} gpio_function_t;

void
gpio_init(void);

int
gpio_set_mode(gpio_t h_self, gpio_mode_t mode);

int
gpio_set_state(gpio_t h_self, gpio_state_t state);

int
gpio_set_alternate_func(gpio_t h_self, gpio_function_t function);

int
gpio_set_pull_down(gpio_t h_self);

#endif