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
    rotate(rotation direction) = 0;

    virtual void
    enable(uint8_t duty_cycle) = 0;

    virtual void
    disable() = 0;
};

} // namespace device
