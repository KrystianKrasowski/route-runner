#include "toggle_sequence_gpio.hpp"
#include <cstdint>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

toggle_sequence_gpio&
toggle_sequence_gpio::of(
    uint32_t timer_port, uint32_t gpio_port, uint16_t gpio_pin
)
{
    static toggle_sequence_gpio device{timer_port, gpio_port, gpio_pin};
    return device;
}

void
toggle_sequence_gpio::change_sequence(uint8_t value)
{
    timer_disable_counter(timer_port);
    gpio_clear(gpio_port, gpio_pin);

    sequence = value;

    timer_enable_counter(timer_port);
}

void
toggle_sequence_gpio::toggle()
{
    (sequence & (1 << sequence_count)) ? gpio_set(gpio_port, gpio_pin)
                                       : gpio_clear(gpio_port, gpio_pin);

    ++sequence_count &= 0x7;
}

} // namespace hardware
