#pragma once

#include "isr_handler.hpp"
#include <libopencm3/cm3/nvic.h>

namespace hardware
{

class toggle_sequence_gpio;

class isr_handler_tim7 : public isr_handler
{
public:

    static isr_handler_tim7&
    of(toggle_sequence_gpio& toggle_sequence);

    void
    handle() override;

private:

    toggle_sequence_gpio& toggle_sequence;

    isr_handler_tim7(toggle_sequence_gpio& toggle_sequence)
        : toggle_sequence{toggle_sequence}
    {
    }
};

} // namespace hardware
