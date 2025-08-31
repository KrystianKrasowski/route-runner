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
        const uint32_t       gpio_1a_port,
        const uint16_t       gpio_1a_pin,
        const uint32_t       gpio_2a_port,
        const uint16_t       gpio_2a_pin,
        const uint32_t       pwm_timer_port,
        const enum tim_oc_id pwm_channel
    );

    void
    rotate(rotation direction) override;

    void
    enable(uint8_t duty_cycle) override;

    void
    disable() override;

private:

    uint32_t       gpio_1a_port_;
    uint32_t       gpio_2a_port_;
    uint32_t       pwm_timer_port_;
    uint16_t       gpio_1a_pin_;
    uint16_t       gpio_2a_pin_;
    enum tim_oc_id pwm_channel_;
};

} // namespace hardware
