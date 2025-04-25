#include "dualshock2.h"
#include "gpio.h"
#include "l293.h"
#include "spi.h"
#include "sysclock.h"
#include "tim.h"
#include <devices/devices.h>

static inline void
configure_tim2(void);

static inline void
configure_tim3(void);

static inline void
configure_spi(void);

static inline void
create_l293_12(void);

static inline void
create_l293_34(void);

static inline void
create_dualshock2_1(void);

void
devices_init(void)
{
    sysclock_init();
    gpio_init();
    tim_init();
    spi_init();

    configure_tim2();
    configure_tim3();
    configure_spi();

    l293_init();
    dualshock2_init();

    create_l293_12();
    create_l293_34();
    create_dualshock2_1();
}

static inline void
configure_tim2(void)
{
    tim_base_conf_t base_conf = {.resolution = 1000, .auto_reload_at = 16};

    tim_event_gen_conf_t event_gen_conf = {
        .reinit_on_update = true,
    };

    tim_base_configure(PERIPH_TIM2, &base_conf);
    tim_event_gen_configure(PERIPH_TIM2, &event_gen_conf);
    tim_interrupt_update_enable(PERIPH_TIM2);
    tim_enable(PERIPH_TIM2);
}

static inline void
configure_tim3(void)
{
    gpio_set_mode(PERIPH_GPIO_PB0, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_mode(PERIPH_GPIO_PB1, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_alternate_func(PERIPH_GPIO_PB0, PERIPH_GPIO_AF_TIM3_CH3);
    gpio_set_alternate_func(PERIPH_GPIO_PB1, PERIPH_GPIO_AF_TIM3_CH4);

    // setting up pull down resistors due to floating state after output compare
    // disable on PWM channel
    gpio_set_pull_down(PERIPH_GPIO_PB0);
    gpio_set_pull_down(PERIPH_GPIO_PB1);

    // 10kHz TIM frequency
    tim_base_conf_t base_conf = {
        .resolution     = 1000000,
        .auto_reload_at = 100,
    };

    // 5kHz PWM signal
    tim_control_conf_t control_conf = {
        .center_aligned_mode = PERIPH_TIM_CENTER_ALIGNED_1,
    };

    tim_event_gen_conf_t event_gen_conf = {
        .reinit_on_update = true,
    };

    tim_oc_conf_t pwm_conf = {
        .default_oc_treshold = 90,
        .oc_mode             = PERIPH_TIM_OC_PWM_1,
        .preload_enable      = true,
    };

    tim_base_configure(PERIPH_TIM3, &base_conf);
    tim_control_configure(PERIPH_TIM3, &control_conf);
    tim_event_gen_configure(PERIPH_TIM3, &event_gen_conf);
    tim_oc_configure(PERIPH_TIM3, PERIPH_TIM_CHANNEL_3, &pwm_conf);
    tim_oc_configure(PERIPH_TIM3, PERIPH_TIM_CHANNEL_4, &pwm_conf);
    tim_enable(PERIPH_TIM3);
}

static inline void
configure_spi(void)
{
    // configure SCK
    gpio_set_mode(PERIPH_GPIO_PB3, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_alternate_func(PERIPH_GPIO_PB3, PERIPH_GPIO_AF_SPI1_SCK);

    // configure MISO
    gpio_set_mode(PERIPH_GPIO_PB4, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_alternate_func(PERIPH_GPIO_PB4, PERIPH_GPIO_AF_SPI1_MISO);

    // configure MOSI
    gpio_set_mode(PERIPH_GPIO_PB5, PERIPH_GPIO_MODE_ALTERNATE);
    gpio_set_alternate_func(PERIPH_GPIO_PB5, PERIPH_GPIO_AF_SPI1_MOSI);

    // configure SPI bus
    spi_set_baud_rate(PERIPH_SPI1, PERIPH_SPI_BR_PRESC_256);
    spi_set_clock_phase(PERIPH_SPI1, PERIPH_SPI_CPHA_DATA_ON_2ND_TRANS);
    spi_set_clock_polarity(PERIPH_SPI1, PERIPH_SPI_CPOL_IDLE_HIGH);
    spi_set_full_duplex(PERIPH_SPI1);
    spi_set_frame_format(PERIPH_SPI1, PERIPH_SPI_FRAME_LSBFIRST);
    spi_set_software_slave_management(PERIPH_SPI1);
    spi_set_master_mode(PERIPH_SPI1);
    spi_set_data_size(PERIPH_SPI1, PERIPH_SPI_DS_8BIT);
    spi_set_rx_interrupts(PERIPH_SPI1, PERIPH_SPI_RX_INTERRUPT_8BIT);
    spi_enable(PERIPH_SPI1);
}

static inline void
create_l293_12(void)
{
    gpio_set_mode(PERIPH_GPIO_PA10, PERIPH_GPIO_MODE_OUTPUT);
    gpio_set_mode(PERIPH_GPIO_PA12, PERIPH_GPIO_MODE_OUTPUT);

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
    gpio_set_mode(PERIPH_GPIO_PB6, PERIPH_GPIO_MODE_OUTPUT);
    gpio_set_mode(PERIPH_GPIO_PB7, PERIPH_GPIO_MODE_OUTPUT);

    l293_instance_t l293_34 = {
        .driver_channel_1 = PERIPH_GPIO_PB6,
        .driver_channel_2 = PERIPH_GPIO_PB7,
        .pwm_timer        = PERIPH_TIM3,
        .pwm_channel      = PERIPH_TIM_CHANNEL_4,
    };

    l293_create(DEVICES_L293_CHANNEL_34, &l293_34);
}

static inline void
create_dualshock2_1(void)
{
    gpio_set_mode(PERIPH_GPIO_PF0, PERIPH_GPIO_MODE_OUTPUT);

    dualshock2_conf_t conf = {
        .device_select = PERIPH_GPIO_PF0,
        .spi_bus       = PERIPH_SPI1,
    };

    dualshock2_create(DEVICES_DUALSHOCK2_1, &conf);
}
