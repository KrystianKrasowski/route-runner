#include "device/tree.hpp"
#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "dualshock2.hpp"
#include "isr_handler_dma1_channel1.hpp"
#include "isr_handler_dma1_channel2.hpp"
#include "isr_handler_tim2.hpp"
#include "isr_handler_tim7.hpp"
#include "isr_registry.hpp"
#include "l293.hpp"
#include "peripherals.hpp"
#include "qtrhd06a.hpp"
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

    auto& blink = hardware::toggle_sequence_gpio::of(TIM7, GPIOA, GPIO8);

    auto& remote_control = hardware::dualshock2::of(
        GPIOF, GPIO0, DMA1, DMA_CHANNEL2, DMA_CHANNEL3, store.p_dualshock2_rbuff
    );

    auto& motor_left =
        hardware::l293::of(GPIOA, GPIO12, GPIOA, GPIO10, TIM3, TIM_OC3);

    auto& motor_right =
        hardware::l293::of(GPIOB, GPIO6, GPIOB, GPIO7, TIM3, TIM_OC4);

    auto& line_sensor = hardware::qtrhd06a::of(
        store.p_qtrhd06a_wbuff, store.qtrhd06a_buffer_length
    );

    auto& isr_handler_tim2 = hardware::isr_handler_tim2::of(remote_control);
    auto& isr_handler_tim7 = hardware::isr_handler_tim7::of(blink);
    auto& isr_handler_dma1_channel2 =
        hardware::isr_handler_dma1_channel2::of(remote_control, store, events);
    auto& isr_handler_dma1_channel1 =
        hardware::isr_handler_dma1_channel1::of(line_sensor, store, events);

    hardware::isr_register(NVIC_TIM2_IRQ, isr_handler_tim2);
    hardware::isr_register(NVIC_TIM7_IRQ, isr_handler_tim7);
    hardware::isr_register(NVIC_DMA1_CHANNEL2_IRQ, isr_handler_dma1_channel2);
    hardware::isr_register(NVIC_DMA1_CHANNEL1_IRQ, isr_handler_dma1_channel1);

    return tree{blink, remote_control, motor_left, motor_right, line_sensor};
}

} // namespace device
