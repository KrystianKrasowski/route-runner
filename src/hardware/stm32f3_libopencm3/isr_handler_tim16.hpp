#pragma once

#include "isr_handler.hpp"

namespace hardware
{

class shell;

class isr_handler_tim16 : public hardware::isr_handler
{
public:

    static isr_handler_tim16&
    of(shell& shell);

    void
    handle() override;

private:

    shell& shell_;

    isr_handler_tim16(shell& shell)
        : shell_{shell}
    {
    }
};

} // namespace hardware
