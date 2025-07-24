#include "isr_registry.hpp"
#include "isr_handler.hpp"
#include <cstdint>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/f3/nvic.h>

namespace hardware
{

isr_handler* tim2_handler          = nullptr;
isr_handler* tim7_handler          = nullptr;
isr_handler* tim15_handler         = nullptr;
isr_handler* dma1_channel2_handler = nullptr;
isr_handler* dma1_channel1_handler = nullptr;

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

    case NVIC_DMA1_CHANNEL2_IRQ:
        nvic_enable_irq(NVIC_DMA1_CHANNEL2_IRQ);
        dma1_channel2_handler = &handler;
        break;

    case NVIC_DMA1_CHANNEL1_IRQ:
        nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
        dma1_channel1_handler = &handler;
        break;
    }
}

} // namespace hardware

extern "C"
{
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
    dma1_channel2_isr()
    {
        if (hardware::dma1_channel2_handler)
        {
            hardware::dma1_channel2_handler->handle();
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
}
