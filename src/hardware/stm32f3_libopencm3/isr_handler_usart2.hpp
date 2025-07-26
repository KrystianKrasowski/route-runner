#pragma once

#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_usart2 : public isr_handler
{
public:

    static isr_handler_usart2&
    of(device::isr_event_emitter& events, data_store& store);

    void
    handle() override;

private:

    device::isr_event_emitter& events_;
    data_store&                store_;

    isr_handler_usart2(device::isr_event_emitter& events, data_store& store)
        : events_{events},
          store_{store}
    {
    }
};

} // namespace hardware
