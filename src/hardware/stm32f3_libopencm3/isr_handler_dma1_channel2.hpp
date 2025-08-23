#pragma once

#include "data_store.hpp"
#include "dualshock2.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_dma1_channel2 : public isr_handler, public isr_events_aware
{
public:

    isr_handler_dma1_channel2(
        dualshock2& remote_control, data_store& data_store
    );

    void
    handle() override;

private:

    dualshock2& remote_control_;
    data_store& data_store_;
};

} // namespace hardware
