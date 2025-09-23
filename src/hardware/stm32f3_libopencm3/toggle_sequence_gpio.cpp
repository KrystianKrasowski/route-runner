#include "toggle_sequence_gpio.hpp"
#include <cstdint>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

toggle_sequence_gpio::toggle_sequence_gpio(
    uint32_t const                   timer_port,
    uint32_t const                   gpio_port,
    uint16_t const                   gpio_pin,
    toggle_sequence_gpio_data* const p_data_store
)
    : timer_port_{timer_port},
      gpio_port_{gpio_port},
      gpio_pin_{gpio_pin},
      p_data_store_{p_data_store}
{
}

void
toggle_sequence_gpio::change_sequence(uint8_t value) const
{
    timer_disable_counter(timer_port_);
    gpio_clear(gpio_port_, gpio_pin_);

    p_data_store_->sequence_ = value;

    timer_enable_counter(timer_port_);
}

void
toggle_sequence_gpio::toggle() const
{
    uint8_t sequence = p_data_store_->sequence_;
    uint8_t count    = p_data_store_->sequence_count_;

    (sequence & (1 << count)) ? gpio_set(gpio_port_, gpio_pin_)
                              : gpio_clear(gpio_port_, gpio_pin_);

    ++p_data_store_->sequence_count_ &= 0x7;
}

} // namespace hardware
