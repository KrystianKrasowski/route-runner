#pragma once

#include "data_store.hpp"
#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_usart2 : public isr_handler, public isr_events_aware
{
public:

    isr_handler_usart2(data_store& store);

    void
    handle() override;

private:

    data_store& store_;
};

} // namespace hardware
