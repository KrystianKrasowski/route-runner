#pragma once

#include "data_store.hpp"
#include "isr_handler.hpp"
#include "qtrhd06a.hpp"

namespace hardware
{

class isr_handler_dma1_channel1 : public isr_handler, public isr_events_aware
{
public:

    isr_handler_dma1_channel1(qtrhd06a& line_sensor, data_store& data_store);

    void
    handle() override;

private:

    qtrhd06a&   line_sensor_;
    data_store& data_store_;
};

} // namespace hardware
