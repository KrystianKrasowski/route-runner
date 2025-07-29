#pragma once

#include <cstdint>

namespace device
{

struct timeout
{
    virtual void
    start(uint16_t millis) = 0;

    virtual void
    stop() = 0;
};

} // namespace device
