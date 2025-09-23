#pragma once

#include <cstdint>

namespace device
{

struct l293
{
    enum rotation
    {
        LEFT,
        RIGHT,
        NONE,
    };

    virtual void
    rotate(rotation direction) const = 0;

    virtual void
    enable(uint8_t duty_cycle) const = 0;

    virtual void
    disable() const = 0;
};

} // namespace device
