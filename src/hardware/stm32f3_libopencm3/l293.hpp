#pragma once

#include "device/l293.hpp"
#include <cstdint>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

class l293 : public device::l293
{
public:

    l293(
        uint32_t const       gpio_1a_port,
        uint16_t const       gpio_1a_pin,
        uint32_t const       gpio_2a_port,
        uint16_t const       gpio_2a_pin,
        uint32_t const       pwm_timer_port,
        enum tim_oc_id const pwm_channel
    );

    void
    rotate(rotation direction) const override;

    void
    enable(uint8_t duty_cycle) const override;

    void
    disable() const override;

private:

    uint32_t const       gpio_1a_port_;
    uint32_t const       gpio_2a_port_;
    uint32_t const       pwm_timer_port_;
    uint16_t const       gpio_1a_pin_;
    uint16_t const       gpio_2a_pin_;
    enum tim_oc_id const pwm_channel_;
};

} // namespace hardware
