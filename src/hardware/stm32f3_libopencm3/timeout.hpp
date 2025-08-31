#pragma once

#include "device/timeout.hpp"
#include <cstdint>

namespace hardware
{

class timeout : public device::timeout
{
public:

    explicit timeout(const uint32_t timer_port);

    void
    start(uint16_t millis) override;

    void
    stop() override;

private:

    const uint32_t timer_port_;
};

} // namespace hardware
