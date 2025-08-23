#include "l293.hpp"
#include "device/l293.hpp"
#include <cstdint>
#include <etl/pool.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

l293::l293(
    const uint32_t       gpio_1a_port,
    const uint16_t       gpio_1a_pin,
    const uint32_t       gpio_2a_port,
    const uint16_t       gpio_2a_pin,
    const uint32_t       pwm_timer_port,
    const enum tim_oc_id pwm_channel
)
    : gpio_1a_port_{gpio_1a_port},
      gpio_2a_port_{gpio_2a_port},
      pwm_timer_port_{pwm_timer_port},
      gpio_1a_pin_{gpio_1a_pin},
      gpio_2a_pin_{gpio_2a_pin},
      pwm_channel_{pwm_channel}
{
}

void
l293::rotate(rotation direction)
{
    switch (direction)
    {
    case LEFT:
        gpio_set(gpio_1a_port_, gpio_1a_pin_);
        gpio_clear(gpio_2a_port_, gpio_2a_pin_);
        break;

    case RIGHT:
        gpio_clear(gpio_1a_port_, gpio_1a_pin_);
        gpio_set(gpio_2a_port_, gpio_2a_pin_);
        break;

    case NONE:
        gpio_clear(gpio_1a_port_, gpio_1a_pin_);
        gpio_clear(gpio_2a_port_, gpio_2a_pin_);
        break;
    }
}

void
l293::enable(uint8_t duty_cycle)
{
    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    timer_set_oc_value(pwm_timer_port_, pwm_channel_, duty_cycle);
    timer_enable_oc_output(pwm_timer_port_, pwm_channel_);
}

void
l293::disable()
{
    timer_disable_oc_output(pwm_timer_port_, pwm_channel_);
}

} // namespace hardware
