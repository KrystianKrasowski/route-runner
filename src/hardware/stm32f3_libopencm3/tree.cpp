#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "device/tree.hpp"
#include "dualshock2.hpp"
#include "isr_handler_dma1_channel2.hpp"
#include "isr_handler_tim2.hpp"
#include "isr_handler_tim7.hpp"
#include "isr_registry.hpp"
#include "peripherals.hpp"
#include "toggle_sequence_gpio.hpp"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace device
{

static hardware::data_store store;

tree
tree::of(isr_event_emitter& events)
{
    hardware::peripherals_setup(store);

    auto& toggle_sequence =
        hardware::toggle_sequence_gpio::of(TIM7, GPIOA, GPIO8);

    auto& dualshock2 = hardware::dualshock2::of(
        GPIOF, GPIO0, DMA1, DMA_CHANNEL2, DMA_CHANNEL3, store.p_dualshock2_rbuff
    );

    auto& isr_handler_tim2 = hardware::isr_handler_tim2::of(dualshock2);
    auto& isr_handler_tim7 = hardware::isr_handler_tim7::of(toggle_sequence);
    auto& isr_handler_dma1_channel2 =
        hardware::isr_handler_dma1_channel2::of(dualshock2, store, events);

    hardware::isr_register(NVIC_TIM2_IRQ, isr_handler_tim2);
    hardware::isr_register(NVIC_TIM7_IRQ, isr_handler_tim7);
    hardware::isr_register(NVIC_DMA1_CHANNEL2_IRQ, isr_handler_dma1_channel2);

    return tree{toggle_sequence, dualshock2};
}

} // namespace device
