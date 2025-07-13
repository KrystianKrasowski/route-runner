#include "peripherals.hpp"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

static inline void
rcc_setup();

static inline void
gpio_setup();

static inline void
tim7_setup();

void
peripherals_setup()
{
    rcc_setup();
    gpio_setup();
    tim7_setup();
}

static inline void
rcc_setup()
{
    rcc_clock_scale sysclock{
        .pllsrc           = RCC_CFGR_PLLSRC_HSI_DIV2,
        .pllmul           = RCC_CFGR_PLLMUL_MUL4,
        .plldiv           = RCC_CFGR2_PREDIV_NODIV,
        .usbdiv1          = false,
        .flash_waitstates = 2,
        .hpre             = RCC_CFGR_HPRE_NODIV,
        .ppre1            = RCC_CFGR_PPRE_DIV2,
        .ppre2            = RCC_CFGR_PPRE_NODIV,
        .power_save       = 0,
        .ahb_frequency    = 16000000,
        .apb1_frequency   = 8000000,
        .apb2_frequency   = 16000000,
    };

    rcc_clock_setup_pll(&sysclock);

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM7);
}

static inline void
gpio_setup()
{
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
}

static inline void
tim7_setup()
{
    // set timer frequency to 1kHz
    timer_set_prescaler(TIM7, 16000 - 1);
    timer_set_period(TIM7, 125 - 1);

    // enable update interrupt
    timer_enable_irq(TIM7, TIM_DIER_UIE);
}

} // namespace hardware
