#pragma once

#include "device/isr_event_emitter.hpp"

namespace hardware
{

class isr_handler
{
public:

    virtual void
    handle() = 0;
};

class isr_events_aware
{
public:

    void
    set_isr_event_emitter(device::isr_event_emitter& events)
    {
        events_ = &events;
    }

    void
    emit_event(device::event_id event_id)
    {
        if (events_)
        {
            events_->emit(event_id);
        }
    }

protected:

    device::isr_event_emitter* events_ = nullptr;
};

} // namespace hardware
