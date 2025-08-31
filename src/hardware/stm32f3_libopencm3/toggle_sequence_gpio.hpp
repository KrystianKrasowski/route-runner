#pragma once

#include "device/toggle_sequence.hpp"
#include "isr_handler_tim7.hpp"
#include <cstdint>

namespace hardware
{

class toggle_sequence_gpio : public device::toggle_sequence
{
public:

    toggle_sequence_gpio(
        const uint32_t timer_port,
        const uint32_t gpio_port,
        const uint16_t gpio_pin
    );

    void
    change_sequence(uint8_t value) override;

private:

    const uint32_t timer_port_;
    const uint32_t gpio_port_;
    const uint16_t gpio_pin_;
    uint8_t        sequence_{0x1};
    uint8_t        sequence_count_{0};

    void
    toggle();

    friend class isr_handler_tim7;
};

} // namespace hardware
