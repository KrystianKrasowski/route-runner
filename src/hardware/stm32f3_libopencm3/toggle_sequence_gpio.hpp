#pragma once

#include "device/toggle_sequence.hpp"
#include "isr_handler_tim7.hpp"
#include <cstdint>

namespace hardware
{

struct toggle_sequence_gpio_data
{
    uint8_t sequence_{0x1};
    uint8_t sequence_count_{0};
};

class toggle_sequence_gpio : public device::toggle_sequence

{
public:

    toggle_sequence_gpio(
        uint32_t const                   timer_port,
        uint32_t const                   gpio_port,
        uint16_t const                   gpio_pin,
        toggle_sequence_gpio_data* const p_data_store
    );

    void
    change_sequence(uint8_t value) const override;

private:

    uint32_t const                   timer_port_;
    uint32_t const                   gpio_port_;
    uint16_t const                   gpio_pin_;
    toggle_sequence_gpio_data* const p_data_store_;

    void
    toggle() const;

    friend class isr_handler_tim7;
};

} // namespace hardware
