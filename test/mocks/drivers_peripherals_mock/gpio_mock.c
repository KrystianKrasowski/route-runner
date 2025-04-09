#include "gpio_mock.h"
#include <stdint.h>
#include <string.h>

#define GPIO_MOCK_BUFFER_SIZE 10

typedef struct gpio_mock
{
    bool         initialized_pins[GPIO_MOCK_BUFFER_SIZE];
    gpio_state_t states[GPIO_MOCK_BUFFER_SIZE];
} gpio_mock_t;

static gpio_mock_t mock = {.initialized_pins = {0}, .states = {0}};

void
gpio_init(gpio_t *self)
{
    mock.initialized_pins[self->pin] = true;
}

void
gpio_set_state(gpio_t *self, gpio_state_t const state)
{
    mock.states[self->pin] = state;
}

bool
gpio_mock_verify_pin_init(gpio_pin_t pin)
{
    return mock.initialized_pins[pin];
}

gpio_state_t
gpio_mock_get_state(gpio_pin_t pin)
{
    return mock.states[pin];
}

void
gpio_mock_reset(void)
{
    memset(&mock.initialized_pins, 0, GPIO_MOCK_BUFFER_SIZE);
    memset(&mock.states, 0, sizeof(mock.states));
}