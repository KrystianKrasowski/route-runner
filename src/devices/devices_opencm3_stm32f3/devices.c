#include "dualshock2.h"
#include "isr_dispatch.h"
#include "l293.h"
#include "spi_transmittion.h"
#include <devices/devices.h>
#include <devices/dualshock2.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/f3/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>

static inline void
sysclock_config(void);

static inline void
rcc_periph_clocks_config(void);

static inline void
nvic_config(void);

static inline void
gpio_config(void);

static inline void
tim2_config(void);

static inline void
tim3_pwm_config(void);

static inline void
spi_config(void);

static inline int
l293_create_channel_12(void);

static inline int
l293_create_channel_34(void);

static inline int
dualshock2_create_device(void);

void
devices_init(void)
{
    isr_dispatch_init();
    sysclock_config();
    rcc_periph_clocks_config();
    nvic_config();
    gpio_config();
    tim2_config();
    tim3_pwm_config();
    spi_config();

    l293_init();
    dualshock2_init();
    spi_transmittion_init();

    // TODO: error handling
    (void)l293_create_channel_12();
    (void)l293_create_channel_34();
    (void)dualshock2_create_device();
}

static inline void
sysclock_config(void)
{
    struct rcc_clock_scale conf = {
        .pllsrc           = RCC_CFGR_PLLSRC_HSI_DIV2,
        .pllmul           = RCC_CFGR_PLLMUL_MUL4,
        .flash_waitstates = 2,
        .hpre             = RCC_CFGR_HPRE_NODIV,
        .ppre1            = RCC_CFGR_PPRE_DIV2,
        .ppre2            = RCC_CFGR_PPRE_NODIV,
        .ahb_frequency    = 16000000,
        .apb1_frequency   = 8000000,
        .apb2_frequency   = 16000000,
    };

    rcc_clock_setup_pll(&conf);
}

static inline void
rcc_periph_clocks_config(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOF);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_SPI1);
}

static inline void
nvic_config(void)
{
    nvic_enable_irq(NVIC_TIM2_IRQ);
    nvic_enable_irq(NVIC_SPI1_IRQ);
}

static inline void
gpio_config(void)
{
    // output compare pins for tim3 pwm signal
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO0);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO0);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO1);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO1);

    // SPI SCK
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO3);

    // SPI MISO
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO4);

    // SPI MOSI
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO5);

    // L293 channel 12
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO10);

    // L293 channel 34
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);

    // dualshock2 spi device select
    gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
}

static inline void
tim2_config(void)
{
    // set the timer to trigger every 16ms
    timer_set_prescaler(TIM2, 16000 - 1);
    timer_set_period(TIM2, 16 - 1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM2, TIM_EGR_UG);

    // prevent from interrupt triggering after reset
    timer_clear_flag(TIM2, TIM_SR_UIF);

    // enable update event interrupt
    timer_enable_irq(TIM2, TIM_DIER_UIE);

    // enable timer
    timer_enable_counter(TIM2);
}

static inline void
tim3_pwm_config(void)
{
    // set timer frequency at 10kHz
    timer_set_prescaler(TIM3, 16 - 1);
    timer_set_period(TIM3, 100 - 1);

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

static inline void
spi_config(void)
{
    spi_disable(SPI1);
    spi_set_baudrate_prescaler(SPI1, SPI_CR1_BR_FPCLK_DIV_256);
    spi_set_clock_phase_1(SPI1);
    spi_set_clock_polarity_1(SPI1);
    spi_set_full_duplex_mode(SPI1);
    spi_send_lsb_first(SPI1);
    spi_enable_software_slave_management(SPI1);
    spi_set_nss_high(SPI1);
    spi_set_master_mode(SPI1);
    spi_set_data_size(SPI1, SPI_CR2_DS_8BIT);
    spi_fifo_reception_threshold_8bit(SPI1);
    spi_enable_rx_buffer_not_empty_interrupt(SPI1);
    spi_enable(SPI1);
}

static inline int
l293_create_channel_12(void)
{
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
l293_create_channel_34(void)
{
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
dualshock2_create_device(void)
{
    dualshock2_conf_t conf = {
        .device_select_port = GPIOF,
        .device_select_pin  = GPIO0,
        .spi_port           = SPI1,
    };

    return dualshock2_create(DEVICE_DUALSHOCK2_1, &conf);
}
