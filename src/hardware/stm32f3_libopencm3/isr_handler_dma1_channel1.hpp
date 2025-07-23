#pragma once

#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "isr_handler.hpp"
#include "qtrhd06a.hpp"

namespace hardware
{

class isr_handler_dma1_channel1 : public isr_handler
{
public:

    static isr_handler_dma1_channel1&
    of(qtrhd06a&                  line_sensor,
       data_store&                data_store,
       device::isr_event_emitter& event_emitter);

    void
    handle() override;

private:

    qtrhd06a&                  line_sensor_;
    data_store&                data_store_;
    device::isr_event_emitter& event_emitter_;

    isr_handler_dma1_channel1(
        qtrhd06a&                  line_sensor,
        data_store&                data_store,
        device::isr_event_emitter& event_emitter
    )
        : line_sensor_{line_sensor},
          data_store_{data_store},
          event_emitter_{event_emitter}
    {
    }
};

} // namespace hardware
