#pragma once

#include "dualshock2.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class dualshock2;

class isr_handler_tim2 : public isr_handler
{
public:

    static isr_handler_tim2&
    of(dualshock2& dualshock2_);

    void
    handle() override;

private:

    dualshock2& dualshock_;

    isr_handler_tim2(dualshock2& dualshock2_)
        : dualshock_{dualshock2_}
    {
    }
};

} // namespace hardware
