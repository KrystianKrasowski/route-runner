#pragma once

#include "device/toggle_sequence.hpp"

namespace app
{

class stack_overflow_handler
{
public:

    static stack_overflow_handler&
    hook(device::toggle_sequence& blink);

    void
    handle();

private:

    device::toggle_sequence& blink_;

    stack_overflow_handler(device::toggle_sequence& blink)
        : blink_{blink}
    {
    }
};

} // namespace app
