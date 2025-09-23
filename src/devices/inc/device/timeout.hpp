#pragma once

#include <cstdint>

namespace device
{

struct timeout
{
    virtual void
    start(uint16_t millis) const = 0;

    virtual void
    stop() const = 0;
};

} // namespace device
