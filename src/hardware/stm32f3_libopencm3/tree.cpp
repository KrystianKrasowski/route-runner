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

static hardware::toggle_sequence_gpio blink{TIM7, GPIOA, GPIO8};

static hardware::dualshock2 remote_control{
    GPIOF, GPIO0, DMA1, DMA_CHANNEL3, DMA_CHANNEL2, store
};

static hardware::l293 motor_left{GPIOA, GPIO12, GPIOA, GPIO10, TIM3, TIM_OC3};

static hardware::l293 motor_right{GPIOB, GPIO6, GPIOB, GPIO7, TIM3, TIM_OC4};

static hardware::qtrhd06a line_sensor{store};

static hardware::timeout offroute_timeout{TIM15};

static hardware::shell shell{store, DMA1, DMA_CHANNEL7};

static hardware::isr_handler_tim2 remote_control_trigger_isr{remote_control};

static hardware::isr_handler_tim7 blink_update_isr{blink};

static hardware::isr_handler_tim15 offroute_timeout_isr;

static hardware::isr_handler_dma1_channel2 remote_control_update_isr{
    remote_control, store
};

static hardware::isr_handler_dma1_channel1 line_sensor_update_isr{
    line_sensor, store
};

static hardware::isr_handler_usart2 shell_new_command_isr{store};

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
tree::init(isr_event_emitter& events) const
{
    hardware::peripherals_setup(store);

    // I'm not 100% convinced this is the best idea, but this way I could avoid
    // cyclic dependency between application and hardware. I suppose one can
    // treat setting isr even emitter port as a part of the peripheral
    // initialization, that must go at the runtime begin.
    // This could probably be avoided by providing isr_event_emitter from some
    // other adapter CMake module
    offroute_timeout_isr.set_isr_event_emitter(events);
    remote_control_update_isr.set_isr_event_emitter(events);
    line_sensor_update_isr.set_isr_event_emitter(events);
    shell_new_command_isr.set_isr_event_emitter(events);

    hardware::isr_register(NVIC_TIM2_IRQ, remote_control_trigger_isr);
    hardware::isr_register(NVIC_TIM7_IRQ, blink_update_isr);
    hardware::isr_register(NVIC_TIM1_BRK_TIM15_IRQ, offroute_timeout_isr);
    hardware::isr_register(NVIC_DMA1_CHANNEL2_IRQ, remote_control_update_isr);
    hardware::isr_register(NVIC_DMA1_CHANNEL1_IRQ, line_sensor_update_isr);
    hardware::isr_register(NVIC_USART2_EXTI26_IRQ, shell_new_command_isr);
}

} // namespace device
