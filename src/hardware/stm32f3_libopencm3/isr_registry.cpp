#include "isr_registry.hpp"
#include "isr_handler.hpp"
#include <cstdint>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>

namespace hardware
{

isr_handler* tim2_handler          = nullptr;
isr_handler* tim7_handler          = nullptr;
isr_handler* tim15_handler         = nullptr;
isr_handler* tim16_handler         = nullptr;
isr_handler* dma1_channel1_handler = nullptr;
isr_handler* dma1_channel2_handler = nullptr;
isr_handler* usart2_handler        = nullptr;

void
isr_register(uint8_t nvic_number, isr_handler& handler)
{
    switch (nvic_number)
    {
    case NVIC_TIM2_IRQ:
        tim2_handler = &handler;
        nvic_enable_irq(NVIC_TIM2_IRQ);
        break;

    case NVIC_TIM7_IRQ:
        tim7_handler = &handler;
        nvic_enable_irq(NVIC_TIM7_IRQ);
        break;

    case NVIC_TIM1_BRK_TIM15_IRQ:
        tim15_handler = &handler;
        nvic_enable_irq(NVIC_TIM1_BRK_TIM15_IRQ);
        break;

    case NVIC_TIM1_UP_TIM16_IRQ:
        tim16_handler = &handler;
        nvic_enable_irq(NVIC_TIM1_UP_TIM16_IRQ);
        break;

    case NVIC_DMA1_CHANNEL1_IRQ:
        dma1_channel1_handler = &handler;
        nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
        break;

    case NVIC_DMA1_CHANNEL2_IRQ:
        dma1_channel2_handler = &handler;
        nvic_enable_irq(NVIC_DMA1_CHANNEL2_IRQ);
        break;

    case NVIC_USART2_EXTI26_IRQ:
        usart2_handler = &handler;
        nvic_enable_irq(NVIC_USART2_EXTI26_IRQ);
        break;
    }
}

} // namespace hardware

extern "C"
{
    uint16_t timer_status_flags = TIM_SR_UIF | TIM_SR_CC1IF | TIM_SR_CC2IF
                                | TIM_SR_CC3IF | TIM_SR_CC4IF | TIM_SR_TIF
                                | TIM_SR_CC1OF | TIM_SR_CC2OF | TIM_SR_CC3OF
                                | TIM_SR_CC4OF;

    uint8_t dma_interrupt_flags = DMA_GIF | DMA_TCIF | DMA_HTIF | DMA_TEIF;

    void
    tim2_isr()
    {
        if (hardware::tim2_handler)
        {
            hardware::tim2_handler->handle();
        }
        else
        {
            timer_clear_flag(TIM2, timer_status_flags);
        }
    }

    void
    tim7_isr()
    {
        if (hardware::tim7_handler)
        {
            hardware::tim7_handler->handle();
        }
        else
        {
            timer_clear_flag(TIM7, timer_status_flags);
        }
    }

    void
    tim1_brk_tim15_isr()
    {
        if (hardware::tim15_handler)
        {
            hardware::tim15_handler->handle();
        }
        else
        {
            timer_clear_flag(TIM15, timer_status_flags);
        }
    }

    void
    tim1_up_tim16_isr()
    {
        if (hardware::tim16_handler)
        {
            hardware::tim16_handler->handle();
        }
        else
        {
            timer_clear_flag(TIM16, timer_status_flags);
        }
    }

    void
    dma1_channel1_isr()
    {
        if (hardware::dma1_channel1_handler)
        {
            hardware::dma1_channel1_handler->handle();
        }
        else
        {
            dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, dma_interrupt_flags);
        }
    }

    void
    dma1_channel2_isr()
    {
        if (hardware::dma1_channel2_handler)
        {
            hardware::dma1_channel2_handler->handle();
        }
        else
        {
            dma_clear_interrupt_flags(DMA1, DMA_CHANNEL2, dma_interrupt_flags);
        }
    }

    void
    usart2_exti26_isr()
    {
        if (hardware::usart2_handler)
        {
            hardware::usart2_handler->handle();
        }
        else
        {
            USART_RQR(USART2) |= USART_RQR_RXFRQ;
        }
    }
}
