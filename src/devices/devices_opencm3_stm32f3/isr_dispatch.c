#include "blink.h"
#include "data_store.h"
#include "dualshock2.h"
#include "isr_dispatch.h"
#include "notification.h"
#include "spi_transmittion.h"
#include <devices/blink.h>
#include <devices/dualshock2.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/f3/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>
#include <utils/result.h>

void
isr_dispatch_init(void)
{
    nvic_enable_irq(NVIC_TIM1_CC_IRQ);
    nvic_enable_irq(NVIC_TIM2_IRQ);
    nvic_enable_irq(NVIC_SPI1_IRQ);
    nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
}

void
tim1_cc_isr(void)
{
    if (timer_get_flag(TIM1, TIM_SR_CC1IF))
    {
        timer_clear_flag(TIM1, TIM_SR_CC1IF);
        blink_update(DEVICE_BLINK_1);
    }
}

void
tim2_isr(void)
{
    if (timer_get_flag(TIM2, TIM_SR_UIF))
    {
        timer_clear_flag(TIM2, TIM_SR_UIF);

        // TODO: DOD
        (void)dualshock2_poll(DEVICE_DUALSHOCK2_1);
    }
}

void
spi1_isr(void)
{
    if (SPI_SR(SPI1) & SPI_SR_TXE)
    {
        uint8_t byte;

        if (spi_transmittion_next_tx_byte(SPI_TRANSMITTION_SPI1, &byte) ==
            RESULT_OK)
        {
            SPI_DR8(SPI1) = byte;
        }
        else
        {
            spi_disable_tx_buffer_empty_interrupt(SPI1);
        }
    }

    if (SPI_SR(SPI1) & SPI_SR_RXNE)
    {
        uint8_t byte = SPI_DR8(SPI1);

        if (spi_transmittion_next_rx_byte(SPI_TRANSMITTION_SPI1, byte) !=
            RESULT_END_OF_BUFFER)
        {
            return;
        }

        uint8_t response[SPI_TRANSMITTION_MAX_SIZE];

        if (spi_transmittion_end(SPI_TRANSMITTION_SPI1, response) == RESULT_OK)
        {
            dualshock2_set_state(DEVICE_DUALSHOCK2_1, response);
        }
    }
}

void
dma1_channel1_isr(void)
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL1, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_TCIF);
        data_store_receive_adc_route();
        notification_give(NOTIFICATION_ROUTE_CONVERSIONS);
    }
}
