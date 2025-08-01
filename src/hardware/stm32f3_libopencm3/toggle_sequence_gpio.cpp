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
    timer_disable_counter(timer_port_);
    gpio_clear(gpio_port_,gpio_pin_);

    sequence_ = value;

    timer_enable_counter(timer_port_);
}

void
toggle_sequence_gpio::toggle()
{
    (sequence_ & (1 <<sequence_count_)) ? gpio_set(gpio_port_,gpio_pin_)
                                       : gpio_clear(gpio_port_,gpio_pin_);

    ++sequence_count_ &= 0x7;
}

} // namespace hardware
