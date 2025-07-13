#include "peripherals.hpp"
#include <cstdint>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

static inline void
rcc_setup();

static inline void
gpio_setup();

static inline void
tim2_setup();

static inline void
tim7_setup();

static inline void
spi_setup();

static inline void
dma1_channel2_setup(uint32_t memory_address);

static inline void
dma1_channel3_setup(uint32_t memory_address);

void
peripherals_setup(data_store& store)
{
    rcc_setup();
    gpio_setup();
    tim2_setup();
    tim7_setup();
    spi_setup();
    dma1_channel2_setup((uint32_t)store.p_dualshock2_wbuff);
    dma1_channel3_setup((uint32_t)store.p_dualshock2_request);
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
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOF);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM7);
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_DMA1);
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
tim7_setup()
{
    // set timer frequency to 1kHz
    timer_set_prescaler(TIM7, 16000 - 1);
    timer_set_period(TIM7, 125 - 1);

    // enable update interrupt
    timer_enable_irq(TIM7, TIM_DIER_UIE);
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

} // namespace hardware
