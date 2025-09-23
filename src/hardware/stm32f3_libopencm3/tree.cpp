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

static hardware::data_store s_store;

// === BLINK ===
static hardware::toggle_sequence_gpio_data s_toggle_sequence_data;

static hardware::toggle_sequence_gpio const s_blink{
    TIM7, GPIOA, GPIO8, &s_toggle_sequence_data
};

// == REMOTE CONTROL ===
static hardware::dualshock2 const s_remote_control{
    GPIOF, GPIO0, DMA1, DMA_CHANNEL3, DMA_CHANNEL2, &s_store
};

static hardware::l293 const s_motor_left{
    GPIOA, GPIO12, GPIOA, GPIO10, TIM3, TIM_OC3
};

static hardware::l293 const s_motor_right{
    GPIOB, GPIO6, GPIOB, GPIO7, TIM3, TIM_OC4
};

static hardware::qtrhd06a const s_line_sensor{&s_store};

static hardware::timeout const s_offroute_timeout{TIM15};

static hardware::shell const s_shell{&s_store, DMA1, DMA_CHANNEL7};

static hardware::isr_handler_tim2 remote_control_trigger_isr{s_remote_control};

static hardware::isr_handler_tim7 blink_update_isr{s_blink};

static hardware::isr_handler_tim15 offroute_timeout_isr;

static hardware::isr_handler_dma1_channel2 remote_control_update_isr{
    s_remote_control, s_store
};

static hardware::isr_handler_dma1_channel1 line_sensor_update_isr{
    s_line_sensor, s_store
};

static hardware::isr_handler_usart2 shell_new_command_isr{s_store};

tree const g_device_tree = {
    s_blink,
    s_remote_control,
    s_motor_left,
    s_motor_right,
    s_line_sensor,
    s_offroute_timeout,
    s_shell
};

void
tree::init(isr_event_emitter& events) const
{
    hardware::peripherals_setup(s_store);

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
