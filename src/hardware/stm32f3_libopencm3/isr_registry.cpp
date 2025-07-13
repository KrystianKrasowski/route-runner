#include "isr_handler.hpp"
#include "isr_registry.hpp"
#include <cstdint>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/f3/nvic.h>

namespace hardware
{

isr_handler *tim7_handler = nullptr;

void
isr_register(uint8_t nvic_number, isr_handler& handler)
{
    switch (nvic_number)
    {
    case NVIC_TIM7_IRQ:
        nvic_enable_irq(NVIC_TIM7_IRQ);
        tim7_handler = &handler;
        break;
    }
}

} // namespace hardware

extern "C"
{
    void
    tim7_isr(void)
    {
        if (hardware::tim7_handler)
        {
            hardware::tim7_handler->handle();
        }
    }
}
