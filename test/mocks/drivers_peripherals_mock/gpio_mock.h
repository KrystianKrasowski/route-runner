#ifndef _GPIO_MOCK_H
#define _GPIO_MOCK_H

#include <gpio.h>
#include <stdbool.h>

bool
gpio_mock_verify_pin_init(gpio_pin_t pin);

gpio_state_t
gpio_mock_get_state(gpio_pin_t pin);

void
gpio_mock_reset(void);

#endif