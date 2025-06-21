#include "data_store.h"
#include "peripherals.h"
#include "systick.h"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <stdint.h>

static inline void
sysclock_config(void);

static inline void
rcc_periph_clocks_config(void);

static inline void
gpio_config(void);

static inline void
tim1_config(void);

static inline void
tim2_config(void);

static inline void
tim3_pwm_config(void);

static inline void
tim6_config(void);

static inline void
tim15_config(void);

static inline void
tim16_config(void);

static inline void
spi_config(void);

static inline void
dma1_channel1_config(void);

static inline void
dma1_channel2_config(void);

static inline void
dma1_channel3_config(void);

static inline void
dma1_channel7_config(void);

static inline void
adc12_config(void);

static inline void
usart2_config(void);

void
peripherals_init(void)
{
    sysclock_config();
    rcc_periph_clocks_config();
    gpio_config();
    tim1_config();
    tim2_config();
    tim3_pwm_config();
    spi_config();
    dma1_channel1_config();
    dma1_channel2_config();
    dma1_channel3_config();
    dma1_channel7_config();
    adc12_config();
    tim6_config();
    tim15_config();
    tim16_config();
    usart2_config();
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
    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_TIM6);
    rcc_periph_clock_enable(RCC_TIM15);
    rcc_periph_clock_enable(RCC_TIM16);
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_ADC12);
    rcc_adc_prescale(RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_2,
                     RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_1);
    rcc_periph_clock_enable(RCC_USART2);
}

static inline void
gpio_config(void)
{
    // output compare pins for tim3 pwm signal
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO0);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO0);
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO1);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO1);

    // output compare pin for state indicator LED
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO8);
    gpio_set_af(GPIOA, GPIO_AF6, GPIO8);

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

    // USART2 receiver
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO15);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO15);

    // USART2 transmitter
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

static inline void
tim1_config(void)
{
    timer_set_prescaler(TIM1, 16000 - 1);
    timer_set_period(TIM1, 125 - 1);
    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_TOGGLE);
    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_break_main_output(TIM1);
    timer_enable_irq(TIM1, TIM_DIER_CC1IE);
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
tim15_config(void)
{
    // set timer frequency to 2Hz
    timer_set_prescaler(TIM15, 16000 - 1);
    timer_set_period(TIM15, 500 - 1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM15, TIM_EGR_UG);
    timer_clear_flag(TIM15, TIM_SR_UIF);

    // enable update interrupt
    timer_enable_irq(TIM15, TIM_DIER_UIE);
}

static inline void
tim16_config(void)
{
    // set timer frequency to 10Hz
    timer_set_prescaler(TIM16, 16000 - 1);
    timer_set_period(TIM16, 100 - 1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM15, TIM_EGR_UG);
    timer_clear_flag(TIM15, TIM_SR_UIF);

    // enable update interrupt
    timer_enable_irq(TIM16, TIM_DIER_UIE);

    // enable timer
    timer_enable_counter(TIM16);
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
    spi_enable_tx_dma(SPI1);
    spi_enable_rx_dma(SPI1);
    spi_enable(SPI1);
}

static inline void
dma1_channel1_config(void)
{
    uint32_t periph_addr = (uint32_t)&ADC12_CDR;
    uint32_t memory_addr = data_store_get_route_wbuff_addr();

    dma_disable_channel(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL1, memory_addr);
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, DATA_STORE_ROUTE_BUFF_LENGTH);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_32BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
    dma_enable_channel(DMA1, DMA_CHANNEL1);
}

static inline void
dma1_channel2_config(void)
{
    uint32_t periph_addr = (uint32_t)&SPI_DR(SPI1);
    uint32_t memory_addr = data_store_get_dualshock2_wbuff_addr();

    dma_disable_channel(DMA1, DMA_CHANNEL2);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL2, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL2, memory_addr);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL2);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL2);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL2, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL2, DMA_CCR_MSIZE_8BIT);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);
}

static inline void
dma1_channel3_config(void)
{
    uint32_t periph_addr = (uint32_t)&SPI_DR(SPI1);
    uint32_t memory_addr = data_store_get_dualshock2_request_addr();

    dma_disable_channel(DMA1, DMA_CHANNEL3);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL3, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL3, memory_addr);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL3);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
}

static inline void
dma1_channel7_config(void)
{
    uint32_t periph_addr = (uint32_t)&USART_TDR(USART2);
    uint32_t memory_addr = data_store_get_serial_txbuff_addr();

    dma_disable_channel(DMA1, DMA_CHANNEL7);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL7, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL7, memory_addr);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL7);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL7);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL7, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL7, DMA_CCR_MSIZE_8BIT);
}

static inline void
adc12_config(void)
{
    // enable voltage regulators
    adc_enable_regulator(ADC1);
    adc_enable_regulator(ADC2);
    systick_delay_us(10);

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

static inline void
usart2_config(void)
{
    usart_set_databits(USART2, 8);
    usart_set_baudrate(USART2, 115200);
    usart_set_stopbits(USART2, USART_CR2_STOPBITS_1);
    usart_enable(USART2);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_enable_rx_interrupt(USART2);
    usart_enable_tx_dma(USART2);
}
