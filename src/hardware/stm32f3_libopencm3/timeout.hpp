#pragma once

#include "device/timeout.hpp"
#include <cstdint>

namespace hardware
{

class timeout : public device::timeout
{
public:

    explicit timeout(uint32_t const timer_port);

    void
    start(uint16_t millis) const override;

    void
    stop() const override;

private:

    uint32_t const timer_port_;
};

} // namespace hardware
