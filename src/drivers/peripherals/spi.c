#include "spi.h"
#include "spi_transfer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stm32f3xx.h>
#include <string.h>

static spi_transfer_t volatile transfer;

static void
transmit_byte_isr(void);

static void
receive_byte_isr(void);

void
spi_init_master(void)
{
    // enable AHB clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // enable APB2 clock access to SPI
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // set PB3 mode to alternate function
    GPIOB->MODER |= GPIO_MODER_MODER3_1;

    // set PB4 mode to alternate function
    GPIOB->MODER |= GPIO_MODER_MODER4_1;

    // set PB5 mode to alternate function
    GPIOB->MODER |= GPIO_MODER_MODER5_1;

    // set PB3 alternate function to SPI SCK (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL3_Pos);

    // set PB4 altrnate function to SPI MISO (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL4_Pos);

    // set PB5 alternate function to SPI MOSI (AF5)
    GPIOB->AFR[0] |= (5 << GPIO_AFRL_AFRL5_Pos);

    // set SPI bus speed to 62.5kHz (8MHz / 128psc)
    SPI1->CR1 |= (6 << SPI_CR1_BR_Pos);

    // set mode 3
    SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;

    // set fullduplex communication
    SPI1->CR1 &= ~SPI_CR1_RXONLY;

    // set LSB first
    SPI1->CR1 |= SPI_CR1_LSBFIRST;

    // set software slave management
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    // set SPI in master mode
    SPI1->CR1 |= SPI_CR1_MSTR;

    // CR2
    // set data lenght to 8bit (DS: 0111)
    SPI1->CR2 &= ~SPI_CR2_DS_3;
    SPI1->CR2 |= SPI_CR2_DS_2;
    SPI1->CR2 |= SPI_CR2_DS_1;
    SPI1->CR2 |= SPI_CR2_DS_0;

    // enable receive interrupts
    SPI1->CR2 |= SPI_CR2_RXNEIE;

    // trigger interrupt wher RX buffer is 8bit long
    SPI1->CR2 |= SPI_CR2_FRXTH;

    // enable SPI
    SPI1->CR1 |= SPI_CR1_SPE;

    // set NVIC for interrupts
    NVIC_EnableIRQ(SPI1_IRQn);

    spi_transfer_init(&transfer);
}

void
spi_transmittion_start(spi_request_t *request)
{
    if (spi_transfer_start(&transfer, request) == SPI_RESULT_SUCCESS)
    {
        SPI1->CR2 |= SPI_CR2_TXEIE;
    }
}

void
SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_TXE)
    {
        transmit_byte_isr();
    }

    if (SPI1->SR & SPI_SR_RXNE)
    {
        receive_byte_isr();
    }
}

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t response[])
{
}

static void
transmit_byte_isr(void)
{
    uint8_t byte;
    if (spi_transfer_next_tx(&transfer, &byte) == SPI_RESULT_SUCCESS)
    {
        *(__IO uint8_t *)(&SPI1->DR) = byte;
    }
    else
    {
        SPI1->CR2 &= ~SPI_CR2_TXEIE;
    }
}

static void
receive_byte_isr(void)
{
    uint8_t byte = (uint8_t)SPI1->DR;
    if (spi_transfer_put_rx(&transfer, byte) == SPI_RESULT_END_OF_RECEPTION)
    {
        uint8_t size = spi_transfer_get_size(&transfer);
        uint8_t response[size];
        spi_transfer_get_response(&transfer, response);
        spi_transfer_init(&transfer);
        spi_on_response_received_isr(response);
    }
}