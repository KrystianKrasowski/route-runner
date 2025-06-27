#include "blink.h"
#include "data_store.h"
#include "dualshock2.h"
#include "isr_dispatch.h"
#include "serial.h"
#include <devices/blink.h>
#include <devices/dualshock2.h>
#include <devices/port.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <stdint.h>
#include <utils/result.h>

void
isr_dispatch_init(void)
{
    nvic_enable_irq(NVIC_TIM1_CC_IRQ);
    nvic_enable_irq(NVIC_TIM1_BRK_TIM15_IRQ);
    nvic_enable_irq(NVIC_TIM1_UP_TIM16_IRQ);
    nvic_enable_irq(NVIC_TIM2_IRQ);
    nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
    nvic_enable_irq(NVIC_DMA1_CHANNEL2_IRQ);
    nvic_enable_irq(NVIC_USART2_EXTI26_IRQ);
}

void
// cppcheck-suppress unusedFunction
tim1_cc_isr(void)
{
    if (timer_get_flag(TIM1, TIM_SR_CC1IF))
    {
        timer_clear_flag(TIM1, TIM_SR_CC1IF);
        blink_update(DEVICE_BLINK_1);
    }
}

void
// cppcheck-suppress unusedFunction
tim1_brk_tim15_isr(void)
{
    if (timer_get_flag(TIM15, TIM_SR_UIF))
    {
        timer_clear_flag(TIM15, TIM_SR_UIF);
        devices_port_isr_notification_give(
            DEVICE_NOTIFICATION_TIMEOUT_GUARD_ROUTE);
    }
}

void
// cppcheck-suppress unusedFunction
tim1_up_tim16_isr(void)
{
    if (timer_get_flag(TIM16, TIM_SR_UIF))
    {
        timer_clear_flag(TIM16, TIM_SR_UIF);
        serial_transmit(DEVICE_SERIAL_1);
    }
}

void
// cppcheck-suppress unusedFunction
tim2_isr(void)
{
    if (timer_get_flag(TIM2, TIM_SR_UIF))
    {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        (void)dualshock2_poll_start(DEVICE_DUALSHOCK2_1);
    }
}

void
// cppcheck-suppress unusedFunction
dma1_channel1_isr(void)
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL1, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_TCIF);
        data_store_update_route();
        devices_port_isr_notification_give(
            DEVICE_NOTIFICATION_ROUTE_CONVERTIONS);
    }
}

void
// cppcheck-suppress unusedFunction
dma1_channel2_isr(void)
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL2, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL2, DMA_TCIF);
        dualshock2_poll_end(DEVICE_DUALSHOCK2_1);
        data_store_update_dualshock2();
        devices_port_isr_notification_give(DEVICE_NOTIFICATION_DUALSHOCK2);
    }
}

void
// cppcheck-suppress unusedFunction
usart2_exti26_isr(void)
{
    if (usart_get_flag(USART2, USART_ISR_RXNE))
    {
        char request = usart_recv(USART2);
        data_store_update_serial_request(request);
        devices_port_isr_notification_give(DEVICE_NOTIFICATION_SERIAL_REQUEST);
    }
}
