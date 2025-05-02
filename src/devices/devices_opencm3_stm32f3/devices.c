#include "l293.h"
#include <devices/devices.h>
#include <libopencm3/stm32/common/timer_common_all.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

static inline void
sysclock_config(void);

static inline void
tim3_pwm_config(void);

static inline int
l293_channel_12_create(void);

static inline int
l293_channel_34_create(void);

static inline int
dualshock2_create(void);

void
devices_init(void)
{
    sysclock_config();
    tim3_pwm_config();

    l293_init();

    // TODO: error handling
    (void)l293_channel_12_create();
    (void)l293_channel_34_create();
    (void)dualshock2_create();
}

static inline void
sysclock_config(void)
{
    // set up 16MHz MCU clock
    rcc_set_sysclk_source(RCC_CFGR_SWS_PLL);
    rcc_set_pll_source(RCC_CFGR_PLLSRC_HSI_DIV2);
    rcc_set_pll_multiplier(RCC_CFGR_PLLMUL_MUL4);
    rcc_osc_on(RCC_PLL);
    rcc_wait_for_osc_ready(RCC_PLL);
}

static inline void
tim3_pwm_config(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_TIM3);

    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO0);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO1);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO0);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO1);

    // set timer frequency at 10kHz
    timer_set_prescaler(TIM3, 16);
    timer_set_period(TIM3, 100);

    // center align mode causes PWM to be at 5kHz frequency
    timer_set_alignment(TIM3, TIM_CR1_CMS_CENTER_1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM3, TIM_EGR_UG);

    // configure PWM on output compare 3
    timer_set_oc_value(TIM3, TIM_OC3, 90);
    timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM3, TIM_OC3);

    // configure PWM on output compare 4
    timer_set_oc_value(TIM3, TIM_OC4, 90);
    timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM3, TIM_OC4);

    // enable the counter
    timer_enable_counter(TIM3);
}

static inline int
l293_channel_12_create(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO10);

    l293_conf_t conf = {
        .gpio_port_1 = GPIOA,
        .gpio_pin_1  = GPIO12,
        .gpio_port_2 = GPIOA,
        .gpio_pin_2  = GPIO10,
        .pwm_timer   = TIM3,
        .pwm_channel = TIM_OC3,
    };

    return l293_create(DEVICE_L293_CHANNEL_12, &conf);
}

static inline int
l293_channel_34_create(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);

    l293_conf_t conf = {
        .gpio_port_1 = GPIOB,
        .gpio_pin_1  = GPIO6,
        .gpio_port_2 = GPIOB,
        .gpio_pin_2  = GPIO7,
        .pwm_timer   = TIM3,
        .pwm_channel = TIM_OC4,
    };

    return l293_create(DEVICE_L293_CHANNEL_34, &conf);
}

static inline int
dualshock2_create(void)
{
    return 0;
}
