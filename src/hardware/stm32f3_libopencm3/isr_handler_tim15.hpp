#pragma once

#include "isr_handler.hpp"

namespace hardware
{

class isr_handler_tim15 : public isr_handler, public isr_events_aware
{
public:

    void
    handle() override;
};

} // namespace hardware
