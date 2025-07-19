#pragma once

#include "device/l293.hpp"
#include <cstdint>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

class l293 : public device::l293
{
public:

    static l293&
    of(uint32_t       gpio_1a_port,
       uint16_t       gpio_1a_pin,
       uint32_t       gpio_2a_port,
       uint16_t       gpio_2a_pin,
       uint32_t       pwm_timer_port,
       enum tim_oc_id pwm_channel);

    void
    rotate(rotation_direction direction) override;

    void
    enable(uint8_t duty_cycle) override;

    void
    disable() override;

private:

    uint32_t       gpio_1a_port_;
    uint16_t       gpio_1a_pin_;
    uint32_t       gpio_2a_port_;
    uint16_t       gpio_2s_pin_;
    uint32_t       pwm_timer_port_;
    enum tim_oc_id pwm_channel_;

    l293(
        uint32_t       gpio_1a_port,
        uint16_t       gpio_1a_pin,
        uint32_t       gpio_2a_port,
        uint16_t       gpio_2a_pin,
        uint32_t       pwm_timer_port,
        enum tim_oc_id pwm_channel
    )
        : gpio_1a_port_{gpio_1a_port},
          gpio_1a_pin_{gpio_1a_pin},
          gpio_2a_port_{gpio_2a_port},
          gpio_2s_pin_{gpio_2a_pin},
          pwm_timer_port_{pwm_timer_port},
          pwm_channel_{pwm_channel}
    {
    }
};

} // namespace hardware
