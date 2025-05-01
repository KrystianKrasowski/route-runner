#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>

static uint8_t volatile toggle = 0;

int
main(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM2);

    nvic_enable_irq(NVIC_TIM2_IRQ);

    timer_set_prescaler(TIM2, 8000 - 1);
    timer_set_period(TIM2, 500 - 1);
    timer_enable_irq(TIM2, TIM_DIER_UIE);
    timer_enable_counter(TIM2);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
    gpio_set(GPIOA, GPIO8);

    while (1)
    {
        if (1 == toggle)
        {
            toggle = 0;
            gpio_toggle(GPIOA, GPIO8);
        }
    }
}

void
tim2_isr(void)
{
    if (timer_get_flag(TIM2, TIM_SR_UIF))
    {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        toggle = 1;
    }
}
