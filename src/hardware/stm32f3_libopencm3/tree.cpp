#include "device/tree.hpp"
#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "dualshock2.hpp"
#include "isr_handler_dma1_channel1.hpp"
#include "isr_handler_dma1_channel2.hpp"
#include "isr_handler_tim15.hpp"
#include "isr_handler_tim16.hpp"
#include "isr_handler_tim2.hpp"
#include "isr_handler_tim7.hpp"
#include "isr_handler_usart2.hpp"
#include "isr_registry.hpp"
#include "l293.hpp"
#include "peripherals.hpp"
#include "qtrhd06a.hpp"
#include "shell.hpp"
#include "timeout.hpp"
#include "toggle_sequence_gpio.hpp"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

namespace device
{

static hardware::data_store store;

hardware::toggle_sequence_gpio blink{TIM7, GPIOA, GPIO8};

hardware::dualshock2 remote_control{
    GPIOF, GPIO0, DMA1, DMA_CHANNEL3, DMA_CHANNEL2, store
};

hardware::l293 motor_left{GPIOA, GPIO12, GPIOA, GPIO10, TIM3, TIM_OC3};

hardware::l293 motor_right{GPIOB, GPIO6, GPIOB, GPIO7, TIM3, TIM_OC4};

hardware::qtrhd06a line_sensor{store};

hardware::timeout offroute_timeout{TIM15};

hardware::shell shell{store, DMA1, DMA_CHANNEL7};

tree g_device_tree = {
    blink,
    remote_control,
    motor_left,
    motor_right,
    line_sensor,
    offroute_timeout,
    shell
};

void
tree::init(isr_event_emitter& events)
{
    hardware::peripherals_setup(store);

    // ISRs
    auto& isr_handler_tim2  = hardware::isr_handler_tim2::of(remote_control);
    auto& isr_handler_tim7  = hardware::isr_handler_tim7::of(blink);
    auto& isr_handler_tim15 = hardware::isr_handler_tim15::of(events);
    auto& isr_handler_dma1_channel2 =
        hardware::isr_handler_dma1_channel2::of(remote_control, store, events);
    auto& isr_handler_dma1_channel1 =
        hardware::isr_handler_dma1_channel1::of(line_sensor, store, events);
    auto& isr_handler_usart2 = hardware::isr_handler_usart2::of(events, store);

    hardware::isr_register(NVIC_TIM2_IRQ, isr_handler_tim2);
    hardware::isr_register(NVIC_TIM7_IRQ, isr_handler_tim7);
    hardware::isr_register(NVIC_TIM1_BRK_TIM15_IRQ, isr_handler_tim15);
    hardware::isr_register(NVIC_DMA1_CHANNEL2_IRQ, isr_handler_dma1_channel2);
    hardware::isr_register(NVIC_DMA1_CHANNEL1_IRQ, isr_handler_dma1_channel1);
    hardware::isr_register(NVIC_USART2_EXTI26_IRQ, isr_handler_usart2);
}

} // namespace device
