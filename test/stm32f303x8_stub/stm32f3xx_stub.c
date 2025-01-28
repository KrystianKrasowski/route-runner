#include "stm32f3xx.h"

RCC_TypeDef rcc = {
    .AHBENR = 0x14
};

GPIO_TypeDef gpioa = {
    .MODER = 0xa8000000,
    .ODR = 0,
    .AFR = {0, 0}
};

GPIO_TypeDef gpiob = {
    .MODER = 0x280,
    .ODR = 0,
    .AFR = {0, 0}
};

SPI_TypeDef spi1 = {
    .CR1 = 0,
    .CR2 = 0x700,
    .SR = 0x2,
    .DR = 0,
    .CRCPR = 0x7,
    .RXCRCR = 0,
    .TXCRCR = 0,
};

RCC_TypeDef *RCC = &rcc;
GPIO_TypeDef *GPIOA = &gpioa;
GPIO_TypeDef *GPIOB = &gpiob;
SPI_TypeDef *SPI1 = &spi1;