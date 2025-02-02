#include "spi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stm32f3xx.h>
#include <string.h>

#define BUFFER_SIZE 15

static volatile uint8_t data_size              = 0;
static volatile uint8_t tx_buffer[BUFFER_SIZE] = {0};
static volatile uint8_t rx_buffer[BUFFER_SIZE] = {0};
static volatile uint8_t tx_index               = 0;
static volatile uint8_t rx_index               = 0;
static volatile bool    transfer_complete      = true;
static volatile gpio_t *select                 = NULL;

static void
transmit_byte_isr(void);

static void
receive_byte_isr(void);

static void
clear_isr(void);

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

    // set SPI bus speed to 250kHz (8MHz / 32psc)
    SPI1->CR1 |= (4 << SPI_CR1_BR_Pos);

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
}

void
spi_transmittion_start(gpio_t *gpio, uint8_t request[], uint8_t size)
{
    if (transfer_complete)
    {
        transfer_complete = false;
        select            = gpio;
        data_size         = size;

        for (uint8_t i = 0; i < size; i++)
        {
            tx_buffer[i] = request[i];
        }

        gpio_set_state(gpio, GPIO_STATE_LOW);

        SPI1->CR2 |= SPI_CR2_TXEIE;
    }
}

void
SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_TXE)
    {
        transmit_byte_isr();
        SPI1->CR2 &= ~SPI_CR2_TXEIE;
    }

    if (SPI1->SR & SPI_SR_RXNE)
    {
        receive_byte_isr();
    }
}

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t volatile resposne[], uint8_t size)
{
}

static void
transmit_byte_isr(void)
{
    if (tx_index < data_size)
    {
        *(__IO uint8_t *)(&SPI1->DR) = tx_buffer[tx_index++];
    }
}

static void
receive_byte_isr(void)
{
    rx_buffer[rx_index++] = (uint8_t)SPI1->DR;

    if (rx_index < data_size)
    {
        SPI1->CR2 |= SPI_CR2_TXEIE;
    }
    else
    {
        gpio_set_state(select, GPIO_STATE_HIGH);
        spi_on_response_received_isr(rx_buffer, data_size);
        clear_isr();
    }
}

static void
clear_isr(void)
{
    data_size         = 0;
    tx_index          = 0;
    rx_index          = 0;
    transfer_complete = true;
    select            = NULL;
}