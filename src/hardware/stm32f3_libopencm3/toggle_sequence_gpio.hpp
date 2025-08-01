#pragma once

#include "device/toggle_sequence.hpp"
#include "isr_handler_tim7.hpp"
#include <cstdint>

namespace hardware
{

class toggle_sequence_gpio : public device::toggle_sequence
{
public:

    static toggle_sequence_gpio&
    of(uint32_t timer_port, uint32_t gpio_port, uint16_t gpio_pin);

    void
    change_sequence(uint8_t value) override;

private:

    uint32_t timer_port_;
    uint32_t gpio_port_;
    uint16_t gpio_pin_;
    uint8_t  sequence_{0x1};
    uint8_t  sequence_count_{0};

    toggle_sequence_gpio(
        uint32_t timer_port, uint32_t gpio_port, uint16_t gpio_pin
    )
        : timer_port_{timer_port}, gpio_port_{gpio_port}, gpio_pin_{gpio_pin}
    {
    }

    void
    toggle();

    friend class isr_handler_tim7;
};

} // namespace hardware
