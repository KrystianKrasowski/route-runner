#include "gpio.h"
#include "l293.h"
#include "sysclock.h"
#include "tim.h"
#include <devices/devices.h>

static inline void
configure_gpios(void);

static inline void
configure_tim3(void);

static inline void
create_l293_12(void);

static inline void
create_l293_34(void);

void
devices_init(void)
{
    sysclock_init();

    gpio_init();
    tim_init();

    configure_gpios();
    configure_tim3();

    l293_init();

    create_l293_12();
    create_l293_34();
}

static inline void
configure_gpios(void)
{
    gpio_set_mode(PERIPH_GPIO_PA10, PERIPH_GPIO_MODE_OUTPUT);
    gpio_set_mode(PERIPH_GPIO_PA12, PERIPH_GPIO_MODE_OUTPUT);
    gpio_set_mode(PERIPH_GPIO_PB6, PERIPH_GPIO_MODE_OUTPUT);
    gpio_set_mode(PERIPH_GPIO_PB7, PERIPH_GPIO_MODE_OUTPUT);
}

static inline void
configure_tim3(void)
{
    gpio_set_mode(PERIPH_GPIO_PB0, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_mode(PERIPH_GPIO_PB1, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_alternate_func(PERIPH_GPIO_PB0, PERIPH_GPIO_AF2);
    gpio_set_alternate_func(PERIPH_GPIO_PB1, PERIPH_GPIO_AF2);

    // setting up pull down resistors due to floating state after output compare
    // disable on PWM channel
    gpio_set_pull_down(PERIPH_GPIO_PB0);
    gpio_set_pull_down(PERIPH_GPIO_PB1);

    // 5kHz PWM signal
    tim_base_conf_t base_config = {
        .resolution             = 1000000,
        .auto_reload_at         = 100,
        .center_aligned_mode    = PERIPH_TIM_CENTER_ALIGNED_1,
        .reinitialize_on_update = true,
    };

    tim_out_compare_conf_t pwm_conf = {
        .default_compare_value = 90,
        .output_compare_mode   = PERIPH_TIM_OUTPUT_COMPARE_PWM_1,
        .preload_enable        = true,
    };

    tim_configure_base(PERIPH_TIM3, &base_config);
    tim_configure_out_compare(PERIPH_TIM3, PERIPH_TIM_CHANNEL_3, &pwm_conf);
    tim_configure_out_compare(PERIPH_TIM3, PERIPH_TIM_CHANNEL_4, &pwm_conf);
    tim_enable(PERIPH_TIM3);
}

static inline void
create_l293_12(void)
{
    l293_instance_t l293_12 = {
        .driver_channel_1 = PERIPH_GPIO_PA12,
        .driver_channel_2 = PERIPH_GPIO_PA10,
        .pwm_timer        = PERIPH_TIM3,
        .pwm_channel      = PERIPH_TIM_CHANNEL_3,
    };

    l293_create(DEVICES_L293_CHANNEL_12, &l293_12);
}

static inline void
create_l293_34(void)
{
    l293_instance_t l293_34 = {
        .driver_channel_1 = PERIPH_GPIO_PB6,
        .driver_channel_2 = PERIPH_GPIO_PB7,
        .pwm_timer        = PERIPH_TIM3,
        .pwm_channel      = PERIPH_TIM_CHANNEL_4,
    };

    l293_create(DEVICES_L293_CHANNEL_34, &l293_34);
}