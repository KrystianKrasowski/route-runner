#include "device/tree.hpp"
#include "isr_handler_tim7.hpp"
#include "isr_registry.hpp"
#include "peripherals.hpp"
#include "toggle_sequence_gpio.hpp"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace device
{

tree
tree::of()
{
    hardware::peripherals_setup();

    auto& toggle_sequence =
        hardware::toggle_sequence_gpio::of(TIM7, GPIOA, GPIO8);

    auto& isr_handler_tim7 = hardware::isr_handler_tim7::of(toggle_sequence);

    hardware::isr_register(NVIC_TIM7_IRQ, isr_handler_tim7);

    return tree{toggle_sequence};
}

} // namespace device
