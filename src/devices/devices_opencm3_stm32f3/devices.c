#include "data_store.h"
#include "dualshock2.h"
#include "isr_dispatch.h"
#include "l293.h"
#include "spi_transmittion.h"
#include <devices/devices.h>
#include <devices/dualshock2.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>

static inline void
sysclock_config(void);

static inline void
rcc_periph_clocks_config(void);

static inline void
gpio_config(void);

static inline void
tim2_config(void);

static inline void
tim6_config(void);

static inline void
tim3_pwm_config(void);

static inline void
spi_config(void);

static inline void
dma1_channel1_config(void);

static inline void
adc12_config(void);

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
    gpio_config();
    tim2_config();
    tim3_pwm_config();
    spi_config();
    dma1_channel1_config();
    adc12_config();
    tim6_config();

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
    rcc_periph_clock_enable(RCC_TIM6);
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_ADC12);
    rcc_adc_prescale(RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_2,
                     RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_1);
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

    // QTR-HD-6A analog inputs
    gpio_mode_setup(GPIOA,
                    GPIO_MODE_ANALOG,
                    GPIO_PUPD_NONE,
                    GPIO1 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);
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
tim6_config(void)
{
    // set timer frequency to 1kHz
    timer_set_prescaler(TIM6, 16 - 1);
    timer_set_period(TIM6, 1000 - 1);

    // enable TRGO on update event
    timer_set_master_mode(TIM6, TIM_CR2_MMS_UPDATE);

    // enable timer
    timer_enable_counter(TIM6);
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

static inline void
dma1_channel1_config(void)
{
    uint32_t memory_addr = data_store_get_adc_route_write_buffer_addr();

    dma_disable_channel(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1, ADC12_CDR);
    dma_set_memory_address(DMA1, DMA_CHANNEL1, memory_addr);
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, ADC_ROUTE_BUFFER_LENGTH);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_32BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
    dma_enable_channel(DMA1, DMA_CHANNEL1);
}

static inline void
adc12_config(void)
{
    adc_enable_regulator(ADC1);
    adc_enable_regulator(ADC2);
    adc_set_multi_mode(ADC1, ADC_CCR_DUAL_REGULAR_SIMUL);

    // enable DMA for dual mode 8-bit
    ADC12_CCR |= ADC_CCR_MDMA_8_6_BIT;

    // enable DMA circular
    ADC12_CCR |= ADC_CCR_DMACFG;

    adc_set_resolution(ADC1, ADC_CFGR1_RES_8_BIT);
    adc_set_resolution(ADC2, ADC_CFGR1_RES_8_BIT);

    adc_set_regular_sequence(ADC1, 4, (uint8_t[]){2, 4, 4, 4});
    adc_set_regular_sequence(ADC2, 4, (uint8_t[]){1, 2, 3, 4});

    adc_enable_external_trigger_regular(
        ADC1, ADC_CFGR1_EXTSEL_VAL(13), ADC_CFGR1_EXTEN_RISING_EDGE);

    adc_power_on(ADC1);
    adc_power_on(ADC2);

    adc_start_conversion_regular(ADC1);
}
