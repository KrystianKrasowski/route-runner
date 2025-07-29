#pragma once

#include "device/timeout.hpp"
#include <cstdint>

namespace hardware
{

class timeout : public device::timeout
{
public:

    static timeout&
    of(uint32_t timer_port);

    void
    start(uint16_t millis) override;

    void
    stop() override;

private:

    uint32_t timer_port_;

    explicit timeout(uint32_t timer_port)
        : timer_port_{timer_port}
    {
    }
};

} // namespace hardware
