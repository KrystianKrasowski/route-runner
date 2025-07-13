#pragma once

#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "dualshock2.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_dma1_channel2 : public isr_handler
{
public:

    static isr_handler_dma1_channel2&
    of(dualshock2&                dualshock2_,
       data_store&                data_store_,
       device::isr_event_emitter& event_emitter_);

    void
    handle() override;

private:

    dualshock2&                dualshock2_;
    data_store&                data_store_;
    device::isr_event_emitter& event_emitter_;

    isr_handler_dma1_channel2(
        dualshock2&                dualshock2,
        data_store&                data_store_,
        device::isr_event_emitter& event_emitter_
    )
        : dualshock2_{dualshock2},
          data_store_{data_store_},
          event_emitter_{event_emitter_}
    {
    }
};

} // namespace hardware
