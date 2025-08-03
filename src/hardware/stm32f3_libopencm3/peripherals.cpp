#include "config.h"
#include "peripherals.hpp"
#include <cstdint>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>

namespace hardware
{

static inline void
rcc_setup();

static inline void
systick_setup();

static inline void
gpio_setup();

static inline void
tim2_setup();

static inline void
tim3_setup();

static inline void
tim6_setup();

static inline void
tim7_setup();

static inline void
tim15_setup();

static inline void
tim16_setup();

static inline void
spi_setup();

static inline void
dma1_channel1_setup(uint32_t memory_address, uint16_t memory_length);

static inline void
dma1_channel2_setup(uint32_t memory_address);

static inline void
dma1_channel3_setup(uint32_t memory_address);

static inline void
dma1_channel7_setup(uint32_t memory_address);

static inline void
adc12_setup();

static inline void
usart2_setup();

static void
systick_delay_us(uint16_t delay)
{
    systick_clear();
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();

    for (uint16_t i = 0; i < delay; i++)
    {
        while ((systick_get_countflag()) == 0)
            ;
    }

    systick_counter_disable();
}

void
peripherals_setup(const data_store& store)
{
    rcc_setup();
    systick_setup();
    gpio_setup();
    tim2_setup();
    tim3_setup();
    spi_setup();
    dma1_channel1_setup(
        (uint32_t)store.p_qtrhd06a_wbuff_, store.QTRHD06A_BUFFER_LENGTH
    );
    dma1_channel2_setup((uint32_t)store.p_dualshock2_wbuff_);
    dma1_channel3_setup((uint32_t)store.p_dualshock2_request_);
    dma1_channel7_setup((uint32_t)store.p_shell_output_);
    adc12_setup();
    tim6_setup();
    tim7_setup();
    tim15_setup();
    tim16_setup();
    usart2_setup();
}

static inline void
rcc_setup()
{
    rcc_clock_scale sysclock;
    sysclock.pllsrc           = RCC_CFGR_PLLSRC_HSI_DIV2;
    sysclock.pllmul           = RCC_CFGR_PLLMUL_MUL4;
    sysclock.plldiv           = RCC_CFGR2_PREDIV_NODIV;
    sysclock.usbdiv1          = false;
    sysclock.flash_waitstates = 2;
    sysclock.hpre             = RCC_CFGR_HPRE_NODIV;
    sysclock.ppre1            = RCC_CFGR_PPRE_DIV2;
    sysclock.ppre2            = RCC_CFGR_PPRE_NODIV;
    sysclock.power_save       = 0;
    sysclock.ahb_frequency    = APP_AHB_FREQUENCY;
    sysclock.apb1_frequency   = APP_APB1_FREQUENCY;
    sysclock.apb2_frequency   = APP_APB2_FREQUENCY;

    rcc_clock_setup_pll(&sysclock);

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOF);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_TIM6);
    rcc_periph_clock_enable(RCC_TIM7);
    rcc_periph_clock_enable(RCC_TIM15);
    rcc_periph_clock_enable(RCC_TIM16);
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_ADC12);
    rcc_adc_prescale(
        RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_2, RCC_CFGR2_ADCxPRES_PLL_CLK_DIV_1
    );
    rcc_periph_clock_enable(RCC_USART2);
}

static inline void
systick_setup()
{
    systick_set_frequency(APP_SYSTICK_FREQUENCY, APP_AHB_FREQUENCY);
}

static inline void
gpio_setup()
{
    // toggle_sequence
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);

    // dualshock2 SPI SCK
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO3);

    // dualshock2 SPI MISO
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO4);

    // dualshock2 SPI MOSI
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5);
    gpio_set_af(GPIOB, GPIO_AF5, GPIO5);

    // dualshock CHIP SELECT
    gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);

    // L293 motor left
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO10);

    // L293 motor right
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);

    // output compare pin for tim3 channel 3
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO0);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO0);

    // output compare pin for tim3 channel 4
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO1);
    gpio_set_af(GPIOB, GPIO_AF2, GPIO1);

    // QTR-HD-6A analog inputs
    gpio_mode_setup(
        GPIOA,
        GPIO_MODE_ANALOG,
        GPIO_PUPD_NONE,
        GPIO1 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7
    );

    // USART2 receiver
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO15);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO15);

    // USART2 transmitter
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

static inline void
tim2_setup()
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
tim3_setup()
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
tim6_setup()
{
    // set timer update to once per 700us
    timer_set_prescaler(TIM6, 16 - 1);
    timer_set_period(TIM6, 700 - 1);

    // enable TRGO on update event
    timer_set_master_mode(TIM6, TIM_CR2_MMS_UPDATE);

    // enable timer
    timer_enable_counter(TIM6);
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

static inline void
tim15_setup()
{
    // set millisecond timer
    timer_set_prescaler(TIM15, 16000 - 1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM15, TIM_EGR_UG);
    timer_clear_flag(TIM15, TIM_SR_UIF);

    // enable update interrupt
    timer_enable_irq(TIM15, TIM_DIER_UIE);
}

static inline void
tim16_setup()
{
    // set timer frequency to 20Hz
    timer_set_prescaler(TIM16, 16000 - 1);
    timer_set_period(TIM16, 50 - 1);

    // reinitialize the counter and update the registers on update event
    timer_generate_event(TIM16, TIM_EGR_UG);
    timer_clear_flag(TIM16, TIM_SR_UIF);

    // enable update interrupt
    timer_enable_irq(TIM16, TIM_DIER_UIE);

    // enable timer
    timer_enable_counter(TIM16);
}

static inline void
spi_setup()
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
dma1_channel1_setup(uint32_t memory_address, uint16_t memory_length)
{
    uint32_t periph_addr = (uint32_t)&ADC12_CDR;

    dma_disable_channel(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL1, memory_address);
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, memory_length);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_32BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
    dma_enable_channel(DMA1, DMA_CHANNEL1);
}

static inline void
dma1_channel2_setup(uint32_t memory_address)
{
    uint32_t periph_addr = (uint32_t)&SPI_DR(SPI1);

    dma_disable_channel(DMA1, DMA_CHANNEL2);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL2, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL2, memory_address);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL2);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL2);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL2, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL2, DMA_CCR_MSIZE_8BIT);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);
}

static inline void
dma1_channel3_setup(uint32_t memory_address)
{
    uint32_t periph_addr = (uint32_t)&SPI_DR(SPI1);

    dma_disable_channel(DMA1, DMA_CHANNEL3);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL3, periph_addr);
    dma_set_memory_address(DMA1, DMA_CHANNEL3, memory_address);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL3);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
}

static inline void
dma1_channel7_setup(uint32_t memory_address)
{
    uint32_t periph_address = (uint32_t)&USART_TDR(USART2);

    dma_disable_channel(DMA1, DMA_CHANNEL7);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL7, periph_address);
    dma_set_memory_address(DMA1, DMA_CHANNEL7, memory_address);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL7);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL7);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL7, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL7, DMA_CCR_MSIZE_8BIT);
}

static inline void
adc12_setup()
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

    const uint8_t sequence_length = 4;

    // adc1 seqeuence needs only 2 channels, 3 and 4 are just dummy values to
    // keep in sync with channel 2
    uint8_t adc1_sequence[sequence_length] = {2, 4, 4, 4};
    uint8_t adc2_sequence[sequence_length] = {1, 2, 3, 4};

    adc_set_regular_sequence(ADC1, sequence_length, adc1_sequence);
    adc_set_regular_sequence(ADC2, sequence_length, adc2_sequence);

    adc_enable_external_trigger_regular(
        ADC1, ADC_CFGR1_EXTSEL_VAL(13), ADC_CFGR1_EXTEN_RISING_EDGE
    );

    adc_power_on(ADC1);
    adc_power_on(ADC2);

    adc_start_conversion_regular(ADC1);
}

static inline void
usart2_setup()
{
    usart_set_databits(USART2, 8);
    usart_set_baudrate(USART2, 115200);
    usart_set_stopbits(USART2, USART_CR2_STOPBITS_1);
    usart_enable(USART2);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_enable_rx_interrupt(USART2);
    usart_enable_tx_dma(USART2);
}

} // namespace hardware
