#include "usart2.h"
#include <stm32f3xx.h>

#define SYS_FREQ        8000000
#define APB1_CLK        SYS_FREQ
#define USART_BAUD_RATE 115200

static uint16_t
compute_usart_bd(uint32_t periphery_clock, uint32_t baud_rate);

int
__io_putchar(int ch)
{
    usart2_tx_write(ch);
    return ch;
}

void
usart2_tx_init(void)
{
    // enable clock access to GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // set PA2 mode to alternate function mode
    GPIOA->MODER &= ~GPIO_MODER_MODER2_0;
    GPIOA->MODER |= GPIO_MODER_MODER2_1;

    // set PA2 alternate function type to USART2_TX - AF7
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFRL2_Pos);

    // enable clock access to USART2
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // configure baud rate
    USART2->BRR = compute_usart_bd(APB1_CLK, USART_BAUD_RATE);

    // configure transfer direction
    USART2->CR1 = USART_CR1_TE;

    // enable USART2 module
    USART2->CR1 |= USART_CR1_UE;
}

void
usart2_tx_write(int chr)
{
    // make sure the transmit data register is empty
	while(!(USART2->ISR & USART_ISR_TXE)) {}

	// write to transmit data register
	USART2->TDR = (chr & 0xff);
}

static uint16_t
compute_usart_bd(uint32_t periphery_clock, uint32_t baud_rate)
{
    return (periphery_clock + (baud_rate / 2U)) / baud_rate;
}