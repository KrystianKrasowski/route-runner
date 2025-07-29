#pragma once

namespace hardware
{

class isr_handler
{
public:

    virtual void
    handle() = 0;
};

} // namespace hardware
