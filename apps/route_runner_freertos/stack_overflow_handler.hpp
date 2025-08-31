#pragma once

#include "device/l293.hpp"
#include "device/toggle_sequence.hpp"

namespace app
{

class stack_overflow_handler
{
public:

    static stack_overflow_handler&
    hook(
        device::toggle_sequence& blink,
        device::l293&            motor_left,
        device::l293&            motor_right
    );

    void
    handle();

private:

    device::toggle_sequence& blink_;
    device::l293&            motor_left_;
    device::l293&            motor_right_;

    explicit stack_overflow_handler(
        device::toggle_sequence& blink,
        device::l293&            motor_left,
        device::l293&            motor_right
    )
        : blink_{blink},
          motor_left_{motor_left},
          motor_right_{motor_right}
    {
    }
};

} // namespace app
