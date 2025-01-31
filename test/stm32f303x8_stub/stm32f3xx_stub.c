#include "stm32f3xx.h"

RCC_TypeDef rcc = {
    .AHBENR  = 0x14,
    .APB1ENR = 0,
    .APB2ENR = 0,
};

GPIO_TypeDef gpioa = {.MODER = 0xa8000000, .ODR = 0, .AFR = {0, 0}};

GPIO_TypeDef gpiob = {.MODER = 0x280, .ODR = 0, .AFR = {0, 0}};

SPI_TypeDef spi1 = {
    .CR1    = 0,
    .CR2    = 0x700,
    .SR     = 0x2,
    .DR     = 0,
    .CRCPR  = 0x7,
    .RXCRCR = 0,
    .TXCRCR = 0,
};

TIM_TypeDef tim3 = {
    .CR1   = 0,
    .CR2   = 0,
    .SMCR  = 0,
    .DIER  = 0,
    .SR    = 0,
    .EGR   = 0,
    .CCMR1 = 0,
    .CCMR2 = 0,
    .CCER  = 0,
    .CNT   = 0,
    .PSC   = 0,
    .ARR   = 0xffffffff,
    .CCR1  = 0,
    .CCR2  = 0,
    .CCR3  = 0,
    .CCR4  = 0,
    .DCR   = 0,
    .DMAR  = 0,
};

RCC_TypeDef  *RCC   = &rcc;
GPIO_TypeDef *GPIOA = &gpioa;
GPIO_TypeDef *GPIOB = &gpiob;
SPI_TypeDef  *SPI1  = &spi1;
TIM_TypeDef  *TIM3  = &tim3;