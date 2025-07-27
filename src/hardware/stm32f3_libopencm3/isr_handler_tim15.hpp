#pragma once

#include "device/isr_event_emitter.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_tim15 : public isr_handler
{
public:

    static isr_handler_tim15&
    of(device::isr_event_emitter& events);

    void
    handle() override;

private:

    device::isr_event_emitter& events_;

    isr_handler_tim15(device::isr_event_emitter& events)
        : events_{events}
    {
    }
};

} // namespace hardware
