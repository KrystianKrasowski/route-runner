#include "isr_registry.hpp"
#include "isr_handler.hpp"
#include <cstdint>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>

namespace hardware
{

// TODO: refactor this to dispatch table

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
        nvic_enable_irq(NVIC_TIM2_IRQ);
        tim2_handler = &handler;
        break;

    case NVIC_TIM7_IRQ:
        nvic_enable_irq(NVIC_TIM7_IRQ);
        tim7_handler = &handler;
        break;

    case NVIC_TIM1_BRK_TIM15_IRQ:
        nvic_enable_irq(NVIC_TIM1_BRK_TIM15_IRQ);
        tim15_handler = &handler;
        break;

    case NVIC_TIM1_UP_TIM16_IRQ:
        nvic_enable_irq(NVIC_TIM1_UP_TIM16_IRQ);
        tim16_handler = &handler;
        break;

    case NVIC_DMA1_CHANNEL1_IRQ:
        nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
        dma1_channel1_handler = &handler;
        break;

    case NVIC_DMA1_CHANNEL2_IRQ:
        nvic_enable_irq(NVIC_DMA1_CHANNEL2_IRQ);
        dma1_channel2_handler = &handler;
        break;

    case NVIC_USART2_EXTI26_IRQ:
        nvic_enable_irq(NVIC_USART2_EXTI26_IRQ);
        usart2_handler = &handler;
        break;
    }
}

} // namespace hardware

extern "C"
{
    // TODO: !!! Refactor these handlers !!!
    // These handlers are not safe. If an interrupt had occured before handlers are
    // assigned, the interrupt flags won't be cleared. Now it works only because
    // the first interrupt occur after assignment, but this is based purely on
    // each device cvonfiguration. The quickest interrupt would be ADC
    // conversion. ADC is triggered every 700us, but it takes 40 conversions,
    // thus DMA triggers apparently after assiginig handlers.
    //
    // The interrupt flag clear should be done here, regardless of handler existance
    void
    tim2_isr()
    {
        if (hardware::tim2_handler)
        {
            hardware::tim2_handler->handle();
        }
    }

    void
    tim7_isr()
    {
        if (hardware::tim7_handler)
        {
            hardware::tim7_handler->handle();
        }
    }

    void
    tim1_brk_tim15_isr()
    {
        if (hardware::tim15_handler)
        {
            hardware::tim15_handler->handle();
        }
    }

    void
    tim1_up_tim16_isr()
    {
        if (hardware::tim16_handler)
        {
            hardware::tim16_handler->handle();
        }
    }

    void
    dma1_channel1_isr()
    {
        if (hardware::dma1_channel1_handler)
        {
            hardware::dma1_channel1_handler->handle();
        }
    }

    void
    dma1_channel2_isr()
    {
        if (hardware::dma1_channel2_handler)
        {
            hardware::dma1_channel2_handler->handle();
        }
    }

    void
    usart2_exti26_isr()
    {
        if (hardware::usart2_handler)
        {
            hardware::usart2_handler->handle();
        }
    }
}
