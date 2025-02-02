#ifndef _STM32F303X8_STUB_H
#define _STM32F303X8_STUB_H

#include "core_cm4_stub.h"
#include <stdint.h>

#define __IO

typedef struct
{
    uint32_t AHBENR;
    uint32_t APB1ENR;
    uint32_t APB2ENR;
} RCC_TypeDef;

typedef struct
{
    uint32_t MODER;
    uint32_t ODR;
    uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct
{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SR;
    uint32_t DR;
    uint32_t CRCPR;
    uint32_t RXCRCR;
    uint32_t TXCRCR;
} SPI_TypeDef;

typedef struct
{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CCMR1;
    uint32_t CCMR2;
    uint32_t CCER;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t RCR;
    uint32_t CCR1;
    uint32_t CCR2;
    uint32_t CCR3;
    uint32_t CCR4;
    uint32_t BDTR;
    uint32_t DCR;
    uint32_t DMAR;
    uint32_t OR;
    uint32_t CCMR3;
    uint32_t CCR5;
    uint32_t CCR6;
} TIM_TypeDef;

typedef struct
{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t BRR;
    uint32_t GTPR;
    uint32_t RTOR;
    uint32_t RQR;
    uint32_t ISR;
    uint32_t ICR;
    uint16_t RDR;
    uint16_t RESERVED1;
    uint16_t TDR;
    uint16_t RESERVED2;
} USART_TypeDef;

extern RCC_TypeDef   *RCC;
extern GPIO_TypeDef  *GPIOA;
extern GPIO_TypeDef  *GPIOB;
extern SPI_TypeDef   *SPI1;
extern TIM_TypeDef   *TIM3;
extern USART_TypeDef *USART2;

/******************  Bit definition for RCC_AHBENR register  ******************/
#define RCC_AHBENR_DMA1EN_Pos  (0U)
#define RCC_AHBENR_DMA1EN_Msk  (0x1UL << RCC_AHBENR_DMA1EN_Pos)
#define RCC_AHBENR_DMA1EN      RCC_AHBENR_DMA1EN_Msk
#define RCC_AHBENR_SRAMEN_Pos  (2U)
#define RCC_AHBENR_SRAMEN_Msk  (0x1UL << RCC_AHBENR_SRAMEN_Pos)
#define RCC_AHBENR_SRAMEN      RCC_AHBENR_SRAMEN_Msk
#define RCC_AHBENR_FLITFEN_Pos (4U)
#define RCC_AHBENR_FLITFEN_Msk (0x1UL << RCC_AHBENR_FLITFEN_Pos)
#define RCC_AHBENR_FLITFEN     RCC_AHBENR_FLITFEN_Msk
#define RCC_AHBENR_CRCEN_Pos   (6U)
#define RCC_AHBENR_CRCEN_Msk   (0x1UL << RCC_AHBENR_CRCEN_Pos)
#define RCC_AHBENR_CRCEN       RCC_AHBENR_CRCEN_Msk
#define RCC_AHBENR_GPIOAEN_Pos (17U)
#define RCC_AHBENR_GPIOAEN_Msk (0x1UL << RCC_AHBENR_GPIOAEN_Pos)
#define RCC_AHBENR_GPIOAEN     RCC_AHBENR_GPIOAEN_Msk
#define RCC_AHBENR_GPIOBEN_Pos (18U)
#define RCC_AHBENR_GPIOBEN_Msk (0x1UL << RCC_AHBENR_GPIOBEN_Pos)
#define RCC_AHBENR_GPIOBEN     RCC_AHBENR_GPIOBEN_Msk
#define RCC_AHBENR_GPIOCEN_Pos (19U)
#define RCC_AHBENR_GPIOCEN_Msk (0x1UL << RCC_AHBENR_GPIOCEN_Pos)
#define RCC_AHBENR_GPIOCEN     RCC_AHBENR_GPIOCEN_Msk
#define RCC_AHBENR_GPIODEN_Pos (20U)
#define RCC_AHBENR_GPIODEN_Msk (0x1UL << RCC_AHBENR_GPIODEN_Pos)
#define RCC_AHBENR_GPIODEN     RCC_AHBENR_GPIODEN_Msk
#define RCC_AHBENR_GPIOFEN_Pos (22U)
#define RCC_AHBENR_GPIOFEN_Msk (0x1UL << RCC_AHBENR_GPIOFEN_Pos)
#define RCC_AHBENR_GPIOFEN     RCC_AHBENR_GPIOFEN_Msk
#define RCC_AHBENR_TSCEN_Pos   (24U)
#define RCC_AHBENR_TSCEN_Msk   (0x1UL << RCC_AHBENR_TSCEN_Pos)
#define RCC_AHBENR_TSCEN       RCC_AHBENR_TSCEN_Msk
#define RCC_AHBENR_ADC12EN_Pos (28U)
#define RCC_AHBENR_ADC12EN_Msk (0x1UL << RCC_AHBENR_ADC12EN_Pos)
#define RCC_AHBENR_ADC12EN     RCC_AHBENR_ADC12EN_Msk

/****************** Bit definition for RCC_APB1ENR register  ******************/
#define RCC_APB1ENR_TIM2EN_Pos   (0U)
#define RCC_APB1ENR_TIM2EN_Msk   (0x1UL << RCC_APB1ENR_TIM2EN_Pos)
#define RCC_APB1ENR_TIM2EN       RCC_APB1ENR_TIM2EN_Msk
#define RCC_APB1ENR_TIM3EN_Pos   (1U)
#define RCC_APB1ENR_TIM3EN_Msk   (0x1UL << RCC_APB1ENR_TIM3EN_Pos)
#define RCC_APB1ENR_TIM3EN       RCC_APB1ENR_TIM3EN_Msk
#define RCC_APB1ENR_TIM6EN_Pos   (4U)
#define RCC_APB1ENR_TIM6EN_Msk   (0x1UL << RCC_APB1ENR_TIM6EN_Pos)
#define RCC_APB1ENR_TIM6EN       RCC_APB1ENR_TIM6EN_Msk
#define RCC_APB1ENR_TIM7EN_Pos   (5U)
#define RCC_APB1ENR_TIM7EN_Msk   (0x1UL << RCC_APB1ENR_TIM7EN_Pos)
#define RCC_APB1ENR_TIM7EN       RCC_APB1ENR_TIM7EN_Msk
#define RCC_APB1ENR_WWDGEN_Pos   (11U)
#define RCC_APB1ENR_WWDGEN_Msk   (0x1UL << RCC_APB1ENR_WWDGEN_Pos)
#define RCC_APB1ENR_WWDGEN       RCC_APB1ENR_WWDGEN_Msk
#define RCC_APB1ENR_USART2EN_Pos (17U)
#define RCC_APB1ENR_USART2EN_Msk (0x1UL << RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN     RCC_APB1ENR_USART2EN_Msk
#define RCC_APB1ENR_USART3EN_Pos (18U)
#define RCC_APB1ENR_USART3EN_Msk (0x1UL << RCC_APB1ENR_USART3EN_Pos)
#define RCC_APB1ENR_USART3EN     RCC_APB1ENR_USART3EN_Msk
#define RCC_APB1ENR_I2C1EN_Pos   (21U)
#define RCC_APB1ENR_I2C1EN_Msk   (0x1UL << RCC_APB1ENR_I2C1EN_Pos)
#define RCC_APB1ENR_I2C1EN       RCC_APB1ENR_I2C1EN_Msk
#define RCC_APB1ENR_CANEN_Pos    (25U)
#define RCC_APB1ENR_CANEN_Msk    (0x1UL << RCC_APB1ENR_CANEN_Pos)
#define RCC_APB1ENR_CANEN        RCC_APB1ENR_CANEN_Msk
#define RCC_APB1ENR_DAC2EN_Pos   (26U)
#define RCC_APB1ENR_DAC2EN_Msk   (0x1UL << RCC_APB1ENR_DAC2EN_Pos)
#define RCC_APB1ENR_DAC2EN       RCC_APB1ENR_DAC2EN_Msk
#define RCC_APB1ENR_PWREN_Pos    (28U)
#define RCC_APB1ENR_PWREN_Msk    (0x1UL << RCC_APB1ENR_PWREN_Pos)
#define RCC_APB1ENR_PWREN        RCC_APB1ENR_PWREN_Msk
#define RCC_APB1ENR_DAC1EN_Pos   (29U)
#define RCC_APB1ENR_DAC1EN_Msk   (0x1UL << RCC_APB1ENR_DAC1EN_Pos)
#define RCC_APB1ENR_DAC1EN       RCC_APB1ENR_DAC1EN_Msk

/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define RCC_APB2ENR_SYSCFGEN_Pos (0U)
#define RCC_APB2ENR_SYSCFGEN_Msk (0x1UL << RCC_APB2ENR_SYSCFGEN_Pos)
#define RCC_APB2ENR_SYSCFGEN     RCC_APB2ENR_SYSCFGEN_Msk
#define RCC_APB2ENR_TIM1EN_Pos   (11U)
#define RCC_APB2ENR_TIM1EN_Msk   (0x1UL << RCC_APB2ENR_TIM1EN_Pos)
#define RCC_APB2ENR_TIM1EN       RCC_APB2ENR_TIM1EN_Msk
#define RCC_APB2ENR_SPI1EN_Pos   (12U)
#define RCC_APB2ENR_SPI1EN_Msk   (0x1UL << RCC_APB2ENR_SPI1EN_Pos)
#define RCC_APB2ENR_SPI1EN       RCC_APB2ENR_SPI1EN_Msk
#define RCC_APB2ENR_USART1EN_Pos (14U)
#define RCC_APB2ENR_USART1EN_Msk (0x1UL << RCC_APB2ENR_USART1EN_Pos)
#define RCC_APB2ENR_USART1EN     RCC_APB2ENR_USART1EN_Msk
#define RCC_APB2ENR_TIM15EN_Pos  (16U)
#define RCC_APB2ENR_TIM15EN_Msk  (0x1UL << RCC_APB2ENR_TIM15EN_Pos)
#define RCC_APB2ENR_TIM15EN      RCC_APB2ENR_TIM15EN_Msk
#define RCC_APB2ENR_TIM16EN_Pos  (17U)
#define RCC_APB2ENR_TIM16EN_Msk  (0x1UL << RCC_APB2ENR_TIM16EN_Pos)
#define RCC_APB2ENR_TIM16EN      RCC_APB2ENR_TIM16EN_Msk
#define RCC_APB2ENR_TIM17EN_Pos  (18U)
#define RCC_APB2ENR_TIM17EN_Msk  (0x1UL << RCC_APB2ENR_TIM17EN_Pos)
#define RCC_APB2ENR_TIM17EN      RCC_APB2ENR_TIM17EN_Msk

/******************************************************************************/
/*                                                                            */
/*                            General Purpose I/O (GPIO)                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODER0_Pos  (0U)
#define GPIO_MODER_MODER0_Msk  (0x3UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER0      GPIO_MODER_MODER0_Msk
#define GPIO_MODER_MODER0_0    (0x1UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER0_1    (0x2UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER1_Pos  (2U)
#define GPIO_MODER_MODER1_Msk  (0x3UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER1      GPIO_MODER_MODER1_Msk
#define GPIO_MODER_MODER1_0    (0x1UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER1_1    (0x2UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER2_Pos  (4U)
#define GPIO_MODER_MODER2_Msk  (0x3UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2      GPIO_MODER_MODER2_Msk
#define GPIO_MODER_MODER2_0    (0x1UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2_1    (0x2UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER3_Pos  (6U)
#define GPIO_MODER_MODER3_Msk  (0x3UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER3      GPIO_MODER_MODER3_Msk
#define GPIO_MODER_MODER3_0    (0x1UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER3_1    (0x2UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER4_Pos  (8U)
#define GPIO_MODER_MODER4_Msk  (0x3UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER4      GPIO_MODER_MODER4_Msk
#define GPIO_MODER_MODER4_0    (0x1UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER4_1    (0x2UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER5_Pos  (10U)
#define GPIO_MODER_MODER5_Msk  (0x3UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5      GPIO_MODER_MODER5_Msk
#define GPIO_MODER_MODER5_0    (0x1UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5_1    (0x2UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER6_Pos  (12U)
#define GPIO_MODER_MODER6_Msk  (0x3UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER6      GPIO_MODER_MODER6_Msk
#define GPIO_MODER_MODER6_0    (0x1UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER6_1    (0x2UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER7_Pos  (14U)
#define GPIO_MODER_MODER7_Msk  (0x3UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER7      GPIO_MODER_MODER7_Msk
#define GPIO_MODER_MODER7_0    (0x1UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER7_1    (0x2UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER8_Pos  (16U)
#define GPIO_MODER_MODER8_Msk  (0x3UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER8      GPIO_MODER_MODER8_Msk
#define GPIO_MODER_MODER8_0    (0x1UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER8_1    (0x2UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER9_Pos  (18U)
#define GPIO_MODER_MODER9_Msk  (0x3UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER9      GPIO_MODER_MODER9_Msk
#define GPIO_MODER_MODER9_0    (0x1UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER9_1    (0x2UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER10_Pos (20U)
#define GPIO_MODER_MODER10_Msk (0x3UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER10     GPIO_MODER_MODER10_Msk
#define GPIO_MODER_MODER10_0   (0x1UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER10_1   (0x2UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER11_Pos (22U)
#define GPIO_MODER_MODER11_Msk (0x3UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER11     GPIO_MODER_MODER11_Msk
#define GPIO_MODER_MODER11_0   (0x1UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER11_1   (0x2UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER12_Pos (24U)
#define GPIO_MODER_MODER12_Msk (0x3UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER12     GPIO_MODER_MODER12_Msk
#define GPIO_MODER_MODER12_0   (0x1UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER12_1   (0x2UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER13_Pos (26U)
#define GPIO_MODER_MODER13_Msk (0x3UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER13     GPIO_MODER_MODER13_Msk
#define GPIO_MODER_MODER13_0   (0x1UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER13_1   (0x2UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER14_Pos (28U)
#define GPIO_MODER_MODER14_Msk (0x3UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER14     GPIO_MODER_MODER14_Msk
#define GPIO_MODER_MODER14_0   (0x1UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER14_1   (0x2UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER15_Pos (30U)
#define GPIO_MODER_MODER15_Msk (0x3UL << GPIO_MODER_MODER15_Pos)
#define GPIO_MODER_MODER15     GPIO_MODER_MODER15_Msk
#define GPIO_MODER_MODER15_0   (0x1UL << GPIO_MODER_MODER15_Pos)
#define GPIO_MODER_MODER15_1   (0x2UL << GPIO_MODER_MODER15_Pos)

/****************** Bit definition for GPIO_AFRL register  ********************/
#define GPIO_AFRL_AFRL0_Pos (0U)
#define GPIO_AFRL_AFRL0_Msk (0xFUL << GPIO_AFRL_AFRL0_Pos)
#define GPIO_AFRL_AFRL0     GPIO_AFRL_AFRL0_Msk
#define GPIO_AFRL_AFRL1_Pos (4U)
#define GPIO_AFRL_AFRL1_Msk (0xFUL << GPIO_AFRL_AFRL1_Pos)
#define GPIO_AFRL_AFRL1     GPIO_AFRL_AFRL1_Msk
#define GPIO_AFRL_AFRL2_Pos (8U)
#define GPIO_AFRL_AFRL2_Msk (0xFUL << GPIO_AFRL_AFRL2_Pos)
#define GPIO_AFRL_AFRL2     GPIO_AFRL_AFRL2_Msk
#define GPIO_AFRL_AFRL3_Pos (12U)
#define GPIO_AFRL_AFRL3_Msk (0xFUL << GPIO_AFRL_AFRL3_Pos)
#define GPIO_AFRL_AFRL3     GPIO_AFRL_AFRL3_Msk
#define GPIO_AFRL_AFRL4_Pos (16U)
#define GPIO_AFRL_AFRL4_Msk (0xFUL << GPIO_AFRL_AFRL4_Pos)
#define GPIO_AFRL_AFRL4     GPIO_AFRL_AFRL4_Msk
#define GPIO_AFRL_AFRL5_Pos (20U)
#define GPIO_AFRL_AFRL5_Msk (0xFUL << GPIO_AFRL_AFRL5_Pos)
#define GPIO_AFRL_AFRL5     GPIO_AFRL_AFRL5_Msk
#define GPIO_AFRL_AFRL6_Pos (24U)
#define GPIO_AFRL_AFRL6_Msk (0xFUL << GPIO_AFRL_AFRL6_Pos)
#define GPIO_AFRL_AFRL6     GPIO_AFRL_AFRL6_Msk
#define GPIO_AFRL_AFRL7_Pos (28U)
#define GPIO_AFRL_AFRL7_Msk (0xFUL << GPIO_AFRL_AFRL7_Pos)
#define GPIO_AFRL_AFRL7     GPIO_AFRL_AFRL7_Msk

/****************** Bit definition for GPIO_AFRH register  ********************/
#define GPIO_AFRH_AFRH0_Pos (0U)
#define GPIO_AFRH_AFRH0_Msk (0xFUL << GPIO_AFRH_AFRH0_Pos)
#define GPIO_AFRH_AFRH0     GPIO_AFRH_AFRH0_Msk
#define GPIO_AFRH_AFRH1_Pos (4U)
#define GPIO_AFRH_AFRH1_Msk (0xFUL << GPIO_AFRH_AFRH1_Pos)
#define GPIO_AFRH_AFRH1     GPIO_AFRH_AFRH1_Msk
#define GPIO_AFRH_AFRH2_Pos (8U)
#define GPIO_AFRH_AFRH2_Msk (0xFUL << GPIO_AFRH_AFRH2_Pos)
#define GPIO_AFRH_AFRH2     GPIO_AFRH_AFRH2_Msk
#define GPIO_AFRH_AFRH3_Pos (12U)
#define GPIO_AFRH_AFRH3_Msk (0xFUL << GPIO_AFRH_AFRH3_Pos)
#define GPIO_AFRH_AFRH3     GPIO_AFRH_AFRH3_Msk
#define GPIO_AFRH_AFRH4_Pos (16U)
#define GPIO_AFRH_AFRH4_Msk (0xFUL << GPIO_AFRH_AFRH4_Pos)
#define GPIO_AFRH_AFRH4     GPIO_AFRH_AFRH4_Msk
#define GPIO_AFRH_AFRH5_Pos (20U)
#define GPIO_AFRH_AFRH5_Msk (0xFUL << GPIO_AFRH_AFRH5_Pos)
#define GPIO_AFRH_AFRH5     GPIO_AFRH_AFRH5_Msk
#define GPIO_AFRH_AFRH6_Pos (24U)
#define GPIO_AFRH_AFRH6_Msk (0xFUL << GPIO_AFRH_AFRH6_Pos)
#define GPIO_AFRH_AFRH6     GPIO_AFRH_AFRH6_Msk
#define GPIO_AFRH_AFRH7_Pos (28U)
#define GPIO_AFRH_AFRH7_Msk (0xFUL << GPIO_AFRH_AFRH7_Pos)
#define GPIO_AFRH_AFRH7     GPIO_AFRH_AFRH7_Msk

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/

/*
 * @brief Specific device feature definitions (not present on all devices in the
 * STM32F3 series)
 */
/* Note: No specific macro feature on this device */

/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_CPHA_Pos     (0U)
#define SPI_CR1_CPHA_Msk     (0x1UL << SPI_CR1_CPHA_Pos)
#define SPI_CR1_CPHA         SPI_CR1_CPHA_Msk
#define SPI_CR1_CPOL_Pos     (1U)
#define SPI_CR1_CPOL_Msk     (0x1UL << SPI_CR1_CPOL_Pos)
#define SPI_CR1_CPOL         SPI_CR1_CPOL_Msk
#define SPI_CR1_MSTR_Pos     (2U)
#define SPI_CR1_MSTR_Msk     (0x1UL << SPI_CR1_MSTR_Pos)
#define SPI_CR1_MSTR         SPI_CR1_MSTR_Msk
#define SPI_CR1_BR_Pos       (3U)
#define SPI_CR1_BR_Msk       (0x7UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR           SPI_CR1_BR_Msk
#define SPI_CR1_BR_0         (0x1UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_1         (0x2UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_2         (0x4UL << SPI_CR1_BR_Pos)
#define SPI_CR1_SPE_Pos      (6U)
#define SPI_CR1_SPE_Msk      (0x1UL << SPI_CR1_SPE_Pos)
#define SPI_CR1_SPE          SPI_CR1_SPE_Msk
#define SPI_CR1_LSBFIRST_Pos (7U)
#define SPI_CR1_LSBFIRST_Msk (0x1UL << SPI_CR1_LSBFIRST_Pos)
#define SPI_CR1_LSBFIRST     SPI_CR1_LSBFIRST_Msk
#define SPI_CR1_SSI_Pos      (8U)
#define SPI_CR1_SSI_Msk      (0x1UL << SPI_CR1_SSI_Pos)
#define SPI_CR1_SSI          SPI_CR1_SSI_Msk
#define SPI_CR1_SSM_Pos      (9U)
#define SPI_CR1_SSM_Msk      (0x1UL << SPI_CR1_SSM_Pos)
#define SPI_CR1_SSM          SPI_CR1_SSM_Msk
#define SPI_CR1_RXONLY_Pos   (10U)
#define SPI_CR1_RXONLY_Msk   (0x1UL << SPI_CR1_RXONLY_Pos)
#define SPI_CR1_RXONLY       SPI_CR1_RXONLY_Msk
#define SPI_CR1_CRCL_Pos     (11U)
#define SPI_CR1_CRCL_Msk     (0x1UL << SPI_CR1_CRCL_Pos)
#define SPI_CR1_CRCL         SPI_CR1_CRCL_Msk
#define SPI_CR1_CRCNEXT_Pos  (12U)
#define SPI_CR1_CRCNEXT_Msk  (0x1UL << SPI_CR1_CRCNEXT_Pos)
#define SPI_CR1_CRCNEXT      SPI_CR1_CRCNEXT_Msk
#define SPI_CR1_CRCEN_Pos    (13U)
#define SPI_CR1_CRCEN_Msk    (0x1UL << SPI_CR1_CRCEN_Pos)
#define SPI_CR1_CRCEN        SPI_CR1_CRCEN_Msk
#define SPI_CR1_BIDIOE_Pos   (14U)
#define SPI_CR1_BIDIOE_Msk   (0x1UL << SPI_CR1_BIDIOE_Pos)
#define SPI_CR1_BIDIOE       SPI_CR1_BIDIOE_Msk
#define SPI_CR1_BIDIMODE_Pos (15U)
#define SPI_CR1_BIDIMODE_Msk (0x1UL << SPI_CR1_BIDIMODE_Pos)
#define SPI_CR1_BIDIMODE     SPI_CR1_BIDIMODE_Msk

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_RXDMAEN_Pos (0U)
#define SPI_CR2_RXDMAEN_Msk (0x1UL << SPI_CR2_RXDMAEN_Pos)
#define SPI_CR2_RXDMAEN     SPI_CR2_RXDMAEN_Msk
#define SPI_CR2_TXDMAEN_Pos (1U)
#define SPI_CR2_TXDMAEN_Msk (0x1UL << SPI_CR2_TXDMAEN_Pos)
#define SPI_CR2_TXDMAEN     SPI_CR2_TXDMAEN_Msk
#define SPI_CR2_SSOE_Pos    (2U)
#define SPI_CR2_SSOE_Msk    (0x1UL << SPI_CR2_SSOE_Pos)
#define SPI_CR2_SSOE        SPI_CR2_SSOE_Msk
#define SPI_CR2_NSSP_Pos    (3U)
#define SPI_CR2_NSSP_Msk    (0x1UL << SPI_CR2_NSSP_Pos)
#define SPI_CR2_NSSP        SPI_CR2_NSSP_Msk
#define SPI_CR2_FRF_Pos     (4U)
#define SPI_CR2_FRF_Msk     (0x1UL << SPI_CR2_FRF_Pos)
#define SPI_CR2_FRF         SPI_CR2_FRF_Msk
#define SPI_CR2_ERRIE_Pos   (5U)
#define SPI_CR2_ERRIE_Msk   (0x1UL << SPI_CR2_ERRIE_Pos)
#define SPI_CR2_ERRIE       SPI_CR2_ERRIE_Msk
#define SPI_CR2_RXNEIE_Pos  (6U)
#define SPI_CR2_RXNEIE_Msk  (0x1UL << SPI_CR2_RXNEIE_Pos)
#define SPI_CR2_RXNEIE      SPI_CR2_RXNEIE_Msk
#define SPI_CR2_TXEIE_Pos   (7U)
#define SPI_CR2_TXEIE_Msk   (0x1UL << SPI_CR2_TXEIE_Pos)
#define SPI_CR2_TXEIE       SPI_CR2_TXEIE_Msk
#define SPI_CR2_DS_Pos      (8U)
#define SPI_CR2_DS_Msk      (0xFUL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS          SPI_CR2_DS_Msk
#define SPI_CR2_DS_0        (0x1UL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_1        (0x2UL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_2        (0x4UL << SPI_CR2_DS_Pos)
#define SPI_CR2_DS_3        (0x8UL << SPI_CR2_DS_Pos)
#define SPI_CR2_FRXTH_Pos   (12U)
#define SPI_CR2_FRXTH_Msk   (0x1UL << SPI_CR2_FRXTH_Pos)
#define SPI_CR2_FRXTH       SPI_CR2_FRXTH_Msk
#define SPI_CR2_LDMARX_Pos  (13U)
#define SPI_CR2_LDMARX_Msk  (0x1UL << SPI_CR2_LDMARX_Pos)
#define SPI_CR2_LDMARX      SPI_CR2_LDMARX_Msk
#define SPI_CR2_LDMATX_Pos  (14U)
#define SPI_CR2_LDMATX_Msk  (0x1UL << SPI_CR2_LDMATX_Pos)
#define SPI_CR2_LDMATX      SPI_CR2_LDMATX_Msk

/********************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXNE_Pos   (0U)
#define SPI_SR_RXNE_Msk   (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE       SPI_SR_RXNE_Msk
#define SPI_SR_TXE_Pos    (1U)
#define SPI_SR_TXE_Msk    (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE        SPI_SR_TXE_Msk
#define SPI_SR_CRCERR_Pos (4U)
#define SPI_SR_CRCERR_Msk (0x1UL << SPI_SR_CRCERR_Pos)
#define SPI_SR_CRCERR     SPI_SR_CRCERR_Msk
#define SPI_SR_MODF_Pos   (5U)
#define SPI_SR_MODF_Msk   (0x1UL << SPI_SR_MODF_Pos)
#define SPI_SR_MODF       SPI_SR_MODF_Msk
#define SPI_SR_OVR_Pos    (6U)
#define SPI_SR_OVR_Msk    (0x1UL << SPI_SR_OVR_Pos)
#define SPI_SR_OVR        SPI_SR_OVR_Msk
#define SPI_SR_BSY_Pos    (7U)
#define SPI_SR_BSY_Msk    (0x1UL << SPI_SR_BSY_Pos)
#define SPI_SR_BSY        SPI_SR_BSY_Msk
#define SPI_SR_FRE_Pos    (8U)
#define SPI_SR_FRE_Msk    (0x1UL << SPI_SR_FRE_Pos)
#define SPI_SR_FRE        SPI_SR_FRE_Msk
#define SPI_SR_FRLVL_Pos  (9U)
#define SPI_SR_FRLVL_Msk  (0x3UL << SPI_SR_FRLVL_Pos)
#define SPI_SR_FRLVL      SPI_SR_FRLVL_Msk
#define SPI_SR_FRLVL_0    (0x1UL << SPI_SR_FRLVL_Pos)
#define SPI_SR_FRLVL_1    (0x2UL << SPI_SR_FRLVL_Pos)
#define SPI_SR_FTLVL_Pos  (11U)
#define SPI_SR_FTLVL_Msk  (0x3UL << SPI_SR_FTLVL_Pos)
#define SPI_SR_FTLVL      SPI_SR_FTLVL_Msk
#define SPI_SR_FTLVL_0    (0x1UL << SPI_SR_FTLVL_Pos)
#define SPI_SR_FTLVL_1    (0x2UL << SPI_SR_FTLVL_Pos)

/********************  Bit definition for SPI_DR register  ********************/
#define SPI_DR_DR_Pos (0U)
#define SPI_DR_DR_Msk (0xFFFFUL << SPI_DR_DR_Pos)
#define SPI_DR_DR     SPI_DR_DR_Msk

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define SPI_CRCPR_CRCPOLY_Pos (0U)
#define SPI_CRCPR_CRCPOLY_Msk (0xFFFFUL << SPI_CRCPR_CRCPOLY_Pos)
#define SPI_CRCPR_CRCPOLY     SPI_CRCPR_CRCPOLY_Msk

/******************  Bit definition for SPI_RXCRCR register  ******************/
#define SPI_RXCRCR_RXCRC_Pos (0U)
#define SPI_RXCRCR_RXCRC_Msk (0xFFFFUL << SPI_RXCRCR_RXCRC_Pos)
#define SPI_RXCRCR_RXCRC     SPI_RXCRCR_RXCRC_Msk

/******************  Bit definition for SPI_TXCRCR register  ******************/
#define SPI_TXCRCR_TXCRC_Pos (0U)
#define SPI_TXCRCR_TXCRC_Msk (0xFFFFUL << SPI_TXCRCR_TXCRC_Pos)
#define SPI_TXCRCR_TXCRC     SPI_TXCRCR_TXCRC_Msk

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define TIM_CR1_CEN_Pos  (0U)
#define TIM_CR1_CEN_Msk  (0x1UL << TIM_CR1_CEN_Pos)
#define TIM_CR1_CEN      TIM_CR1_CEN_Msk
#define TIM_CR1_UDIS_Pos (1U)
#define TIM_CR1_UDIS_Msk (0x1UL << TIM_CR1_UDIS_Pos)
#define TIM_CR1_UDIS     TIM_CR1_UDIS_Msk
#define TIM_CR1_URS_Pos  (2U)
#define TIM_CR1_URS_Msk  (0x1UL << TIM_CR1_URS_Pos)
#define TIM_CR1_URS      TIM_CR1_URS_Msk
#define TIM_CR1_OPM_Pos  (3U)
#define TIM_CR1_OPM_Msk  (0x1UL << TIM_CR1_OPM_Pos)
#define TIM_CR1_OPM      TIM_CR1_OPM_Msk
#define TIM_CR1_DIR_Pos  (4U)
#define TIM_CR1_DIR_Msk  (0x1UL << TIM_CR1_DIR_Pos)
#define TIM_CR1_DIR      TIM_CR1_DIR_Msk

#define TIM_CR1_CMS_Pos (5U)
#define TIM_CR1_CMS_Msk (0x3UL << TIM_CR1_CMS_Pos)
#define TIM_CR1_CMS     TIM_CR1_CMS_Msk
#define TIM_CR1_CMS_0   (0x1UL << TIM_CR1_CMS_Pos)
#define TIM_CR1_CMS_1   (0x2UL << TIM_CR1_CMS_Pos)

#define TIM_CR1_ARPE_Pos (7U)
#define TIM_CR1_ARPE_Msk (0x1UL << TIM_CR1_ARPE_Pos)
#define TIM_CR1_ARPE     TIM_CR1_ARPE_Msk

#define TIM_CR1_CKD_Pos (8U)
#define TIM_CR1_CKD_Msk (0x3UL << TIM_CR1_CKD_Pos)
#define TIM_CR1_CKD     TIM_CR1_CKD_Msk
#define TIM_CR1_CKD_0   (0x1UL << TIM_CR1_CKD_Pos)
#define TIM_CR1_CKD_1   (0x2UL << TIM_CR1_CKD_Pos)

#define TIM_CR1_UIFREMAP_Pos (11U)
#define TIM_CR1_UIFREMAP_Msk (0x1UL << TIM_CR1_UIFREMAP_Pos)
#define TIM_CR1_UIFREMAP     TIM_CR1_UIFREMAP_Msk

/*******************  Bit definition for TIM_CR2 register  ********************/
#define TIM_CR2_CCPC_Pos (0U)
#define TIM_CR2_CCPC_Msk (0x1UL << TIM_CR2_CCPC_Pos)
#define TIM_CR2_CCPC     TIM_CR2_CCPC_Msk
#define TIM_CR2_CCUS_Pos (2U)
#define TIM_CR2_CCUS_Msk (0x1UL << TIM_CR2_CCUS_Pos)
#define TIM_CR2_CCUS     TIM_CR2_CCUS_Msk
#define TIM_CR2_CCDS_Pos (3U)
#define TIM_CR2_CCDS_Msk (0x1UL << TIM_CR2_CCDS_Pos)
#define TIM_CR2_CCDS     TIM_CR2_CCDS_Msk

#define TIM_CR2_MMS_Pos (4U)
#define TIM_CR2_MMS_Msk (0x7UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS     TIM_CR2_MMS_Msk
#define TIM_CR2_MMS_0   (0x1UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_1   (0x2UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_2   (0x4UL << TIM_CR2_MMS_Pos)

#define TIM_CR2_TI1S_Pos  (7U)
#define TIM_CR2_TI1S_Msk  (0x1UL << TIM_CR2_TI1S_Pos)
#define TIM_CR2_TI1S      TIM_CR2_TI1S_Msk
#define TIM_CR2_OIS1_Pos  (8U)
#define TIM_CR2_OIS1_Msk  (0x1UL << TIM_CR2_OIS1_Pos)
#define TIM_CR2_OIS1      TIM_CR2_OIS1_Msk
#define TIM_CR2_OIS1N_Pos (9U)
#define TIM_CR2_OIS1N_Msk (0x1UL << TIM_CR2_OIS1N_Pos)
#define TIM_CR2_OIS1N     TIM_CR2_OIS1N_Msk
#define TIM_CR2_OIS2_Pos  (10U)
#define TIM_CR2_OIS2_Msk  (0x1UL << TIM_CR2_OIS2_Pos)
#define TIM_CR2_OIS2      TIM_CR2_OIS2_Msk
#define TIM_CR2_OIS2N_Pos (11U)
#define TIM_CR2_OIS2N_Msk (0x1UL << TIM_CR2_OIS2N_Pos)
#define TIM_CR2_OIS2N     TIM_CR2_OIS2N_Msk
#define TIM_CR2_OIS3_Pos  (12U)
#define TIM_CR2_OIS3_Msk  (0x1UL << TIM_CR2_OIS3_Pos)
#define TIM_CR2_OIS3      TIM_CR2_OIS3_Msk
#define TIM_CR2_OIS3N_Pos (13U)
#define TIM_CR2_OIS3N_Msk (0x1UL << TIM_CR2_OIS3N_Pos)
#define TIM_CR2_OIS3N     TIM_CR2_OIS3N_Msk
#define TIM_CR2_OIS4_Pos  (14U)
#define TIM_CR2_OIS4_Msk  (0x1UL << TIM_CR2_OIS4_Pos)
#define TIM_CR2_OIS4      TIM_CR2_OIS4_Msk

#define TIM_CR2_OIS5_Pos (16U)
#define TIM_CR2_OIS5_Msk (0x1UL << TIM_CR2_OIS5_Pos)
#define TIM_CR2_OIS5     TIM_CR2_OIS5_Msk
#define TIM_CR2_OIS6_Pos (18U)
#define TIM_CR2_OIS6_Msk (0x1UL << TIM_CR2_OIS6_Pos)
#define TIM_CR2_OIS6     TIM_CR2_OIS6_Msk

#define TIM_CR2_MMS2_Pos (20U)
#define TIM_CR2_MMS2_Msk (0xFUL << TIM_CR2_MMS2_Pos)
#define TIM_CR2_MMS2     TIM_CR2_MMS2_Msk
#define TIM_CR2_MMS2_0   (0x1UL << TIM_CR2_MMS2_Pos)
#define TIM_CR2_MMS2_1   (0x2UL << TIM_CR2_MMS2_Pos)
#define TIM_CR2_MMS2_2   (0x4UL << TIM_CR2_MMS2_Pos)
#define TIM_CR2_MMS2_3   (0x8UL << TIM_CR2_MMS2_Pos)

/*******************  Bit definition for TIM_SMCR register  *******************/
#define TIM_SMCR_SMS_Pos (0U)
#define TIM_SMCR_SMS_Msk (0x10007UL << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS     TIM_SMCR_SMS_Msk
#define TIM_SMCR_SMS_0   (0x00000001U)
#define TIM_SMCR_SMS_1   (0x00000002U)
#define TIM_SMCR_SMS_2   (0x00000004U)
#define TIM_SMCR_SMS_3   (0x00010000U)

#define TIM_SMCR_OCCS_Pos (3U)
#define TIM_SMCR_OCCS_Msk (0x1UL << TIM_SMCR_OCCS_Pos)
#define TIM_SMCR_OCCS     TIM_SMCR_OCCS_Msk

#define TIM_SMCR_TS_Pos (4U)
#define TIM_SMCR_TS_Msk (0x7UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS     TIM_SMCR_TS_Msk
#define TIM_SMCR_TS_0   (0x1UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_1   (0x2UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_2   (0x4UL << TIM_SMCR_TS_Pos)

#define TIM_SMCR_MSM_Pos (7U)
#define TIM_SMCR_MSM_Msk (0x1UL << TIM_SMCR_MSM_Pos)
#define TIM_SMCR_MSM     TIM_SMCR_MSM_Msk

#define TIM_SMCR_ETF_Pos (8U)
#define TIM_SMCR_ETF_Msk (0xFUL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF     TIM_SMCR_ETF_Msk
#define TIM_SMCR_ETF_0   (0x1UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_1   (0x2UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_2   (0x4UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_3   (0x8UL << TIM_SMCR_ETF_Pos)

#define TIM_SMCR_ETPS_Pos (12U)
#define TIM_SMCR_ETPS_Msk (0x3UL << TIM_SMCR_ETPS_Pos)
#define TIM_SMCR_ETPS     TIM_SMCR_ETPS_Msk
#define TIM_SMCR_ETPS_0   (0x1UL << TIM_SMCR_ETPS_Pos)
#define TIM_SMCR_ETPS_1   (0x2UL << TIM_SMCR_ETPS_Pos)

#define TIM_SMCR_ECE_Pos (14U)
#define TIM_SMCR_ECE_Msk (0x1UL << TIM_SMCR_ECE_Pos)
#define TIM_SMCR_ECE     TIM_SMCR_ECE_Msk
#define TIM_SMCR_ETP_Pos (15U)
#define TIM_SMCR_ETP_Msk (0x1UL << TIM_SMCR_ETP_Pos)
#define TIM_SMCR_ETP     TIM_SMCR_ETP_Msk

/*******************  Bit definition for TIM_DIER register  *******************/
#define TIM_DIER_UIE_Pos   (0U)
#define TIM_DIER_UIE_Msk   (0x1UL << TIM_DIER_UIE_Pos)
#define TIM_DIER_UIE       TIM_DIER_UIE_Msk
#define TIM_DIER_CC1IE_Pos (1U)
#define TIM_DIER_CC1IE_Msk (0x1UL << TIM_DIER_CC1IE_Pos)
#define TIM_DIER_CC1IE     TIM_DIER_CC1IE_Msk
#define TIM_DIER_CC2IE_Pos (2U)
#define TIM_DIER_CC2IE_Msk (0x1UL << TIM_DIER_CC2IE_Pos)
#define TIM_DIER_CC2IE     TIM_DIER_CC2IE_Msk
#define TIM_DIER_CC3IE_Pos (3U)
#define TIM_DIER_CC3IE_Msk (0x1UL << TIM_DIER_CC3IE_Pos)
#define TIM_DIER_CC3IE     TIM_DIER_CC3IE_Msk
#define TIM_DIER_CC4IE_Pos (4U)
#define TIM_DIER_CC4IE_Msk (0x1UL << TIM_DIER_CC4IE_Pos)
#define TIM_DIER_CC4IE     TIM_DIER_CC4IE_Msk
#define TIM_DIER_COMIE_Pos (5U)
#define TIM_DIER_COMIE_Msk (0x1UL << TIM_DIER_COMIE_Pos)
#define TIM_DIER_COMIE     TIM_DIER_COMIE_Msk
#define TIM_DIER_TIE_Pos   (6U)
#define TIM_DIER_TIE_Msk   (0x1UL << TIM_DIER_TIE_Pos)
#define TIM_DIER_TIE       TIM_DIER_TIE_Msk
#define TIM_DIER_BIE_Pos   (7U)
#define TIM_DIER_BIE_Msk   (0x1UL << TIM_DIER_BIE_Pos)
#define TIM_DIER_BIE       TIM_DIER_BIE_Msk
#define TIM_DIER_UDE_Pos   (8U)
#define TIM_DIER_UDE_Msk   (0x1UL << TIM_DIER_UDE_Pos)
#define TIM_DIER_UDE       TIM_DIER_UDE_Msk
#define TIM_DIER_CC1DE_Pos (9U)
#define TIM_DIER_CC1DE_Msk (0x1UL << TIM_DIER_CC1DE_Pos)
#define TIM_DIER_CC1DE     TIM_DIER_CC1DE_Msk
#define TIM_DIER_CC2DE_Pos (10U)
#define TIM_DIER_CC2DE_Msk (0x1UL << TIM_DIER_CC2DE_Pos)
#define TIM_DIER_CC2DE     TIM_DIER_CC2DE_Msk
#define TIM_DIER_CC3DE_Pos (11U)
#define TIM_DIER_CC3DE_Msk (0x1UL << TIM_DIER_CC3DE_Pos)
#define TIM_DIER_CC3DE     TIM_DIER_CC3DE_Msk
#define TIM_DIER_CC4DE_Pos (12U)
#define TIM_DIER_CC4DE_Msk (0x1UL << TIM_DIER_CC4DE_Pos)
#define TIM_DIER_CC4DE     TIM_DIER_CC4DE_Msk
#define TIM_DIER_COMDE_Pos (13U)
#define TIM_DIER_COMDE_Msk (0x1UL << TIM_DIER_COMDE_Pos)
#define TIM_DIER_COMDE     TIM_DIER_COMDE_Msk
#define TIM_DIER_TDE_Pos   (14U)
#define TIM_DIER_TDE_Msk   (0x1UL << TIM_DIER_TDE_Pos)
#define TIM_DIER_TDE       TIM_DIER_TDE_Msk

/********************  Bit definition for TIM_SR register  ********************/
#define TIM_SR_UIF_Pos   (0U)
#define TIM_SR_UIF_Msk   (0x1UL << TIM_SR_UIF_Pos)
#define TIM_SR_UIF       TIM_SR_UIF_Msk
#define TIM_SR_CC1IF_Pos (1U)
#define TIM_SR_CC1IF_Msk (0x1UL << TIM_SR_CC1IF_Pos)
#define TIM_SR_CC1IF     TIM_SR_CC1IF_Msk
#define TIM_SR_CC2IF_Pos (2U)
#define TIM_SR_CC2IF_Msk (0x1UL << TIM_SR_CC2IF_Pos)
#define TIM_SR_CC2IF     TIM_SR_CC2IF_Msk
#define TIM_SR_CC3IF_Pos (3U)
#define TIM_SR_CC3IF_Msk (0x1UL << TIM_SR_CC3IF_Pos)
#define TIM_SR_CC3IF     TIM_SR_CC3IF_Msk
#define TIM_SR_CC4IF_Pos (4U)
#define TIM_SR_CC4IF_Msk (0x1UL << TIM_SR_CC4IF_Pos)
#define TIM_SR_CC4IF     TIM_SR_CC4IF_Msk
#define TIM_SR_COMIF_Pos (5U)
#define TIM_SR_COMIF_Msk (0x1UL << TIM_SR_COMIF_Pos)
#define TIM_SR_COMIF     TIM_SR_COMIF_Msk
#define TIM_SR_TIF_Pos   (6U)
#define TIM_SR_TIF_Msk   (0x1UL << TIM_SR_TIF_Pos)
#define TIM_SR_TIF       TIM_SR_TIF_Msk
#define TIM_SR_BIF_Pos   (7U)
#define TIM_SR_BIF_Msk   (0x1UL << TIM_SR_BIF_Pos)
#define TIM_SR_BIF       TIM_SR_BIF_Msk
#define TIM_SR_B2IF_Pos  (8U)
#define TIM_SR_B2IF_Msk  (0x1UL << TIM_SR_B2IF_Pos)
#define TIM_SR_B2IF      TIM_SR_B2IF_Msk
#define TIM_SR_CC1OF_Pos (9U)
#define TIM_SR_CC1OF_Msk (0x1UL << TIM_SR_CC1OF_Pos)
#define TIM_SR_CC1OF     TIM_SR_CC1OF_Msk
#define TIM_SR_CC2OF_Pos (10U)
#define TIM_SR_CC2OF_Msk (0x1UL << TIM_SR_CC2OF_Pos)
#define TIM_SR_CC2OF     TIM_SR_CC2OF_Msk
#define TIM_SR_CC3OF_Pos (11U)
#define TIM_SR_CC3OF_Msk (0x1UL << TIM_SR_CC3OF_Pos)
#define TIM_SR_CC3OF     TIM_SR_CC3OF_Msk
#define TIM_SR_CC4OF_Pos (12U)
#define TIM_SR_CC4OF_Msk (0x1UL << TIM_SR_CC4OF_Pos)
#define TIM_SR_CC4OF     TIM_SR_CC4OF_Msk
#define TIM_SR_CC5IF_Pos (16U)
#define TIM_SR_CC5IF_Msk (0x1UL << TIM_SR_CC5IF_Pos)
#define TIM_SR_CC5IF     TIM_SR_CC5IF_Msk
#define TIM_SR_CC6IF_Pos (17U)
#define TIM_SR_CC6IF_Msk (0x1UL << TIM_SR_CC6IF_Pos)
#define TIM_SR_CC6IF     TIM_SR_CC6IF_Msk

/*******************  Bit definition for TIM_EGR register  ********************/
#define TIM_EGR_UG_Pos   (0U)
#define TIM_EGR_UG_Msk   (0x1UL << TIM_EGR_UG_Pos)
#define TIM_EGR_UG       TIM_EGR_UG_Msk
#define TIM_EGR_CC1G_Pos (1U)
#define TIM_EGR_CC1G_Msk (0x1UL << TIM_EGR_CC1G_Pos)
#define TIM_EGR_CC1G     TIM_EGR_CC1G_Msk
#define TIM_EGR_CC2G_Pos (2U)
#define TIM_EGR_CC2G_Msk (0x1UL << TIM_EGR_CC2G_Pos)
#define TIM_EGR_CC2G     TIM_EGR_CC2G_Msk
#define TIM_EGR_CC3G_Pos (3U)
#define TIM_EGR_CC3G_Msk (0x1UL << TIM_EGR_CC3G_Pos)
#define TIM_EGR_CC3G     TIM_EGR_CC3G_Msk
#define TIM_EGR_CC4G_Pos (4U)
#define TIM_EGR_CC4G_Msk (0x1UL << TIM_EGR_CC4G_Pos)
#define TIM_EGR_CC4G     TIM_EGR_CC4G_Msk
#define TIM_EGR_COMG_Pos (5U)
#define TIM_EGR_COMG_Msk (0x1UL << TIM_EGR_COMG_Pos)
#define TIM_EGR_COMG     TIM_EGR_COMG_Msk
#define TIM_EGR_TG_Pos   (6U)
#define TIM_EGR_TG_Msk   (0x1UL << TIM_EGR_TG_Pos)
#define TIM_EGR_TG       TIM_EGR_TG_Msk
#define TIM_EGR_BG_Pos   (7U)
#define TIM_EGR_BG_Msk   (0x1UL << TIM_EGR_BG_Pos)
#define TIM_EGR_BG       TIM_EGR_BG_Msk
#define TIM_EGR_B2G_Pos  (8U)
#define TIM_EGR_B2G_Msk  (0x1UL << TIM_EGR_B2G_Pos)
#define TIM_EGR_B2G      TIM_EGR_B2G_Msk

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define TIM_CCMR1_CC1S_Pos (0U)
#define TIM_CCMR1_CC1S_Msk (0x3UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S     TIM_CCMR1_CC1S_Msk
#define TIM_CCMR1_CC1S_0   (0x1UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S_1   (0x2UL << TIM_CCMR1_CC1S_Pos)

#define TIM_CCMR1_OC1FE_Pos (2U)
#define TIM_CCMR1_OC1FE_Msk (0x1UL << TIM_CCMR1_OC1FE_Pos)
#define TIM_CCMR1_OC1FE     TIM_CCMR1_OC1FE_Msk
#define TIM_CCMR1_OC1PE_Pos (3U)
#define TIM_CCMR1_OC1PE_Msk (0x1UL << TIM_CCMR1_OC1PE_Pos)
#define TIM_CCMR1_OC1PE     TIM_CCMR1_OC1PE_Msk

#define TIM_CCMR1_OC1M_Pos (4U)
#define TIM_CCMR1_OC1M_Msk (0x1007UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M     TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1M_0   (0x00000010U)
#define TIM_CCMR1_OC1M_1   (0x00000020U)
#define TIM_CCMR1_OC1M_2   (0x00000040U)
#define TIM_CCMR1_OC1M_3   (0x00010000U)

#define TIM_CCMR1_OC1CE_Pos (7U)
#define TIM_CCMR1_OC1CE_Msk (0x1UL << TIM_CCMR1_OC1CE_Pos)
#define TIM_CCMR1_OC1CE     TIM_CCMR1_OC1CE_Msk

#define TIM_CCMR1_CC2S_Pos (8U)
#define TIM_CCMR1_CC2S_Msk (0x3UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S     TIM_CCMR1_CC2S_Msk
#define TIM_CCMR1_CC2S_0   (0x1UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S_1   (0x2UL << TIM_CCMR1_CC2S_Pos)

#define TIM_CCMR1_OC2FE_Pos (10U)
#define TIM_CCMR1_OC2FE_Msk (0x1UL << TIM_CCMR1_OC2FE_Pos)
#define TIM_CCMR1_OC2FE     TIM_CCMR1_OC2FE_Msk
#define TIM_CCMR1_OC2PE_Pos (11U)
#define TIM_CCMR1_OC2PE_Msk (0x1UL << TIM_CCMR1_OC2PE_Pos)
#define TIM_CCMR1_OC2PE     TIM_CCMR1_OC2PE_Msk

#define TIM_CCMR1_OC2M_Pos (12U)
#define TIM_CCMR1_OC2M_Msk (0x1007UL << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2M     TIM_CCMR1_OC2M_Msk
#define TIM_CCMR1_OC2M_0   (0x00001000U)
#define TIM_CCMR1_OC2M_1   (0x00002000U)
#define TIM_CCMR1_OC2M_2   (0x00004000U)
#define TIM_CCMR1_OC2M_3   (0x01000000U)

#define TIM_CCMR1_OC2CE_Pos (15U)
#define TIM_CCMR1_OC2CE_Msk (0x1UL << TIM_CCMR1_OC2CE_Pos)
#define TIM_CCMR1_OC2CE     TIM_CCMR1_OC2CE_Msk

/*----------------------------------------------------------------------------*/

#define TIM_CCMR1_IC1PSC_Pos (2U)
#define TIM_CCMR1_IC1PSC_Msk (0x3UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_CCMR1_IC1PSC     TIM_CCMR1_IC1PSC_Msk
#define TIM_CCMR1_IC1PSC_0   (0x1UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_CCMR1_IC1PSC_1   (0x2UL << TIM_CCMR1_IC1PSC_Pos)

#define TIM_CCMR1_IC1F_Pos (4U)
#define TIM_CCMR1_IC1F_Msk (0xFUL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F     TIM_CCMR1_IC1F_Msk
#define TIM_CCMR1_IC1F_0   (0x1UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_1   (0x2UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_2   (0x4UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_3   (0x8UL << TIM_CCMR1_IC1F_Pos)

#define TIM_CCMR1_IC2PSC_Pos (10U)
#define TIM_CCMR1_IC2PSC_Msk (0x3UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_CCMR1_IC2PSC     TIM_CCMR1_IC2PSC_Msk
#define TIM_CCMR1_IC2PSC_0   (0x1UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_CCMR1_IC2PSC_1   (0x2UL << TIM_CCMR1_IC2PSC_Pos)

#define TIM_CCMR1_IC2F_Pos (12U)
#define TIM_CCMR1_IC2F_Msk (0xFUL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F     TIM_CCMR1_IC2F_Msk
#define TIM_CCMR1_IC2F_0   (0x1UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_1   (0x2UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_2   (0x4UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_3   (0x8UL << TIM_CCMR1_IC2F_Pos)

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define TIM_CCMR2_CC3S_Pos (0U)
#define TIM_CCMR2_CC3S_Msk (0x3UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC3S     TIM_CCMR2_CC3S_Msk
#define TIM_CCMR2_CC3S_0   (0x1UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC3S_1   (0x2UL << TIM_CCMR2_CC3S_Pos)

#define TIM_CCMR2_OC3FE_Pos (2U)
#define TIM_CCMR2_OC3FE_Msk (0x1UL << TIM_CCMR2_OC3FE_Pos)
#define TIM_CCMR2_OC3FE     TIM_CCMR2_OC3FE_Msk
#define TIM_CCMR2_OC3PE_Pos (3U)
#define TIM_CCMR2_OC3PE_Msk (0x1UL << TIM_CCMR2_OC3PE_Pos)
#define TIM_CCMR2_OC3PE     TIM_CCMR2_OC3PE_Msk

#define TIM_CCMR2_OC3M_Pos (4U)
#define TIM_CCMR2_OC3M_Msk (0x1007UL << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3M     TIM_CCMR2_OC3M_Msk
#define TIM_CCMR2_OC3M_0   (0x00000010U)
#define TIM_CCMR2_OC3M_1   (0x00000020U)
#define TIM_CCMR2_OC3M_2   (0x00000040U)
#define TIM_CCMR2_OC3M_3   (0x00010000U)

#define TIM_CCMR2_OC3CE_Pos (7U)
#define TIM_CCMR2_OC3CE_Msk (0x1UL << TIM_CCMR2_OC3CE_Pos)
#define TIM_CCMR2_OC3CE     TIM_CCMR2_OC3CE_Msk

#define TIM_CCMR2_CC4S_Pos (8U)
#define TIM_CCMR2_CC4S_Msk (0x3UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR2_CC4S     TIM_CCMR2_CC4S_Msk
#define TIM_CCMR2_CC4S_0   (0x1UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR2_CC4S_1   (0x2UL << TIM_CCMR2_CC4S_Pos)

#define TIM_CCMR2_OC4FE_Pos (10U)
#define TIM_CCMR2_OC4FE_Msk (0x1UL << TIM_CCMR2_OC4FE_Pos)
#define TIM_CCMR2_OC4FE     TIM_CCMR2_OC4FE_Msk
#define TIM_CCMR2_OC4PE_Pos (11U)
#define TIM_CCMR2_OC4PE_Msk (0x1UL << TIM_CCMR2_OC4PE_Pos)
#define TIM_CCMR2_OC4PE     TIM_CCMR2_OC4PE_Msk

#define TIM_CCMR2_OC4M_Pos (12U)
#define TIM_CCMR2_OC4M_Msk (0x1007UL << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4M     TIM_CCMR2_OC4M_Msk
#define TIM_CCMR2_OC4M_0   (0x00001000U)
#define TIM_CCMR2_OC4M_1   (0x00002000U)
#define TIM_CCMR2_OC4M_2   (0x00004000U)
#define TIM_CCMR2_OC4M_3   (0x01000000U)

#define TIM_CCMR2_OC4CE_Pos (15U)
#define TIM_CCMR2_OC4CE_Msk (0x1UL << TIM_CCMR2_OC4CE_Pos)
#define TIM_CCMR2_OC4CE     TIM_CCMR2_OC4CE_Msk

/*----------------------------------------------------------------------------*/

#define TIM_CCMR2_IC3PSC_Pos (2U)
#define TIM_CCMR2_IC3PSC_Msk (0x3UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_CCMR2_IC3PSC     TIM_CCMR2_IC3PSC_Msk
#define TIM_CCMR2_IC3PSC_0   (0x1UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_CCMR2_IC3PSC_1   (0x2UL << TIM_CCMR2_IC3PSC_Pos)

#define TIM_CCMR2_IC3F_Pos (4U)
#define TIM_CCMR2_IC3F_Msk (0xFUL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F     TIM_CCMR2_IC3F_Msk
#define TIM_CCMR2_IC3F_0   (0x1UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_1   (0x2UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_2   (0x4UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_3   (0x8UL << TIM_CCMR2_IC3F_Pos)

#define TIM_CCMR2_IC4PSC_Pos (10U)
#define TIM_CCMR2_IC4PSC_Msk (0x3UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_CCMR2_IC4PSC     TIM_CCMR2_IC4PSC_Msk
#define TIM_CCMR2_IC4PSC_0   (0x1UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_CCMR2_IC4PSC_1   (0x2UL << TIM_CCMR2_IC4PSC_Pos)

#define TIM_CCMR2_IC4F_Pos (12U)
#define TIM_CCMR2_IC4F_Msk (0xFUL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F     TIM_CCMR2_IC4F_Msk
#define TIM_CCMR2_IC4F_0   (0x1UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_1   (0x2UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_2   (0x4UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_3   (0x8UL << TIM_CCMR2_IC4F_Pos)

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CCER_CC1E_Pos  (0U)
#define TIM_CCER_CC1E_Msk  (0x1UL << TIM_CCER_CC1E_Pos)
#define TIM_CCER_CC1E      TIM_CCER_CC1E_Msk
#define TIM_CCER_CC1P_Pos  (1U)
#define TIM_CCER_CC1P_Msk  (0x1UL << TIM_CCER_CC1P_Pos)
#define TIM_CCER_CC1P      TIM_CCER_CC1P_Msk
#define TIM_CCER_CC1NE_Pos (2U)
#define TIM_CCER_CC1NE_Msk (0x1UL << TIM_CCER_CC1NE_Pos)
#define TIM_CCER_CC1NE     TIM_CCER_CC1NE_Msk
#define TIM_CCER_CC1NP_Pos (3U)
#define TIM_CCER_CC1NP_Msk (0x1UL << TIM_CCER_CC1NP_Pos)
#define TIM_CCER_CC1NP     TIM_CCER_CC1NP_Msk
#define TIM_CCER_CC2E_Pos  (4U)
#define TIM_CCER_CC2E_Msk  (0x1UL << TIM_CCER_CC2E_Pos)
#define TIM_CCER_CC2E      TIM_CCER_CC2E_Msk
#define TIM_CCER_CC2P_Pos  (5U)
#define TIM_CCER_CC2P_Msk  (0x1UL << TIM_CCER_CC2P_Pos)
#define TIM_CCER_CC2P      TIM_CCER_CC2P_Msk
#define TIM_CCER_CC2NE_Pos (6U)
#define TIM_CCER_CC2NE_Msk (0x1UL << TIM_CCER_CC2NE_Pos)
#define TIM_CCER_CC2NE     TIM_CCER_CC2NE_Msk
#define TIM_CCER_CC2NP_Pos (7U)
#define TIM_CCER_CC2NP_Msk (0x1UL << TIM_CCER_CC2NP_Pos)
#define TIM_CCER_CC2NP     TIM_CCER_CC2NP_Msk
#define TIM_CCER_CC3E_Pos  (8U)
#define TIM_CCER_CC3E_Msk  (0x1UL << TIM_CCER_CC3E_Pos)
#define TIM_CCER_CC3E      TIM_CCER_CC3E_Msk
#define TIM_CCER_CC3P_Pos  (9U)
#define TIM_CCER_CC3P_Msk  (0x1UL << TIM_CCER_CC3P_Pos)
#define TIM_CCER_CC3P      TIM_CCER_CC3P_Msk
#define TIM_CCER_CC3NE_Pos (10U)
#define TIM_CCER_CC3NE_Msk (0x1UL << TIM_CCER_CC3NE_Pos)
#define TIM_CCER_CC3NE     TIM_CCER_CC3NE_Msk
#define TIM_CCER_CC3NP_Pos (11U)
#define TIM_CCER_CC3NP_Msk (0x1UL << TIM_CCER_CC3NP_Pos)
#define TIM_CCER_CC3NP     TIM_CCER_CC3NP_Msk
#define TIM_CCER_CC4E_Pos  (12U)
#define TIM_CCER_CC4E_Msk  (0x1UL << TIM_CCER_CC4E_Pos)
#define TIM_CCER_CC4E      TIM_CCER_CC4E_Msk
#define TIM_CCER_CC4P_Pos  (13U)
#define TIM_CCER_CC4P_Msk  (0x1UL << TIM_CCER_CC4P_Pos)
#define TIM_CCER_CC4P      TIM_CCER_CC4P_Msk
#define TIM_CCER_CC4NP_Pos (15U)
#define TIM_CCER_CC4NP_Msk (0x1UL << TIM_CCER_CC4NP_Pos)
#define TIM_CCER_CC4NP     TIM_CCER_CC4NP_Msk
#define TIM_CCER_CC5E_Pos  (16U)
#define TIM_CCER_CC5E_Msk  (0x1UL << TIM_CCER_CC5E_Pos)
#define TIM_CCER_CC5E      TIM_CCER_CC5E_Msk
#define TIM_CCER_CC5P_Pos  (17U)
#define TIM_CCER_CC5P_Msk  (0x1UL << TIM_CCER_CC5P_Pos)
#define TIM_CCER_CC5P      TIM_CCER_CC5P_Msk
#define TIM_CCER_CC6E_Pos  (20U)
#define TIM_CCER_CC6E_Msk  (0x1UL << TIM_CCER_CC6E_Pos)
#define TIM_CCER_CC6E      TIM_CCER_CC6E_Msk
#define TIM_CCER_CC6P_Pos  (21U)
#define TIM_CCER_CC6P_Msk  (0x1UL << TIM_CCER_CC6P_Pos)
#define TIM_CCER_CC6P      TIM_CCER_CC6P_Msk

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT_Pos    (0U)
#define TIM_CNT_CNT_Msk    (0xFFFFFFFFUL << TIM_CNT_CNT_Pos)
#define TIM_CNT_CNT        TIM_CNT_CNT_Msk
#define TIM_CNT_UIFCPY_Pos (31U)
#define TIM_CNT_UIFCPY_Msk (0x1UL << TIM_CNT_UIFCPY_Pos)
#define TIM_CNT_UIFCPY     TIM_CNT_UIFCPY_Msk

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC_Pos (0U)
#define TIM_PSC_PSC_Msk (0xFFFFUL << TIM_PSC_PSC_Pos)
#define TIM_PSC_PSC     TIM_PSC_PSC_Msk

/*******************  Bit definition for TIM_ARR register  ********************/
#define TIM_ARR_ARR_Pos (0U)
#define TIM_ARR_ARR_Msk (0xFFFFFFFFUL << TIM_ARR_ARR_Pos)
#define TIM_ARR_ARR     TIM_ARR_ARR_Msk

/*******************  Bit definition for TIM_RCR register  ********************/
#define TIM_RCR_REP_Pos (0U)
#define TIM_RCR_REP_Msk (0xFFFFUL << TIM_RCR_REP_Pos)
#define TIM_RCR_REP     TIM_RCR_REP_Msk

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define TIM_CCR1_CCR1_Pos (0U)
#define TIM_CCR1_CCR1_Msk (0xFFFFUL << TIM_CCR1_CCR1_Pos)
#define TIM_CCR1_CCR1     TIM_CCR1_CCR1_Msk

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define TIM_CCR2_CCR2_Pos (0U)
#define TIM_CCR2_CCR2_Msk (0xFFFFUL << TIM_CCR2_CCR2_Pos)
#define TIM_CCR2_CCR2     TIM_CCR2_CCR2_Msk

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define TIM_CCR3_CCR3_Pos (0U)
#define TIM_CCR3_CCR3_Msk (0xFFFFUL << TIM_CCR3_CCR3_Pos)
#define TIM_CCR3_CCR3     TIM_CCR3_CCR3_Msk

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define TIM_CCR4_CCR4_Pos (0U)
#define TIM_CCR4_CCR4_Msk (0xFFFFUL << TIM_CCR4_CCR4_Pos)
#define TIM_CCR4_CCR4     TIM_CCR4_CCR4_Msk

/*******************  Bit definition for TIM_CCR5 register  *******************/
#define TIM_CCR5_CCR5_Pos  (0U)
#define TIM_CCR5_CCR5_Msk  (0xFFFFFFFFUL << TIM_CCR5_CCR5_Pos)
#define TIM_CCR5_CCR5      TIM_CCR5_CCR5_Msk
#define TIM_CCR5_GC5C1_Pos (29U)
#define TIM_CCR5_GC5C1_Msk (0x1UL << TIM_CCR5_GC5C1_Pos)
#define TIM_CCR5_GC5C1     TIM_CCR5_GC5C1_Msk
#define TIM_CCR5_GC5C2_Pos (30U)
#define TIM_CCR5_GC5C2_Msk (0x1UL << TIM_CCR5_GC5C2_Pos)
#define TIM_CCR5_GC5C2     TIM_CCR5_GC5C2_Msk
#define TIM_CCR5_GC5C3_Pos (31U)
#define TIM_CCR5_GC5C3_Msk (0x1UL << TIM_CCR5_GC5C3_Pos)
#define TIM_CCR5_GC5C3     TIM_CCR5_GC5C3_Msk

/*******************  Bit definition for TIM_CCR6 register  *******************/
#define TIM_CCR6_CCR6_Pos (0U)
#define TIM_CCR6_CCR6_Msk (0xFFFFUL << TIM_CCR6_CCR6_Pos)
#define TIM_CCR6_CCR6     TIM_CCR6_CCR6_Msk

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_BDTR_DTG_Pos (0U)
#define TIM_BDTR_DTG_Msk (0xFFUL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG     TIM_BDTR_DTG_Msk
#define TIM_BDTR_DTG_0   (0x01UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_1   (0x02UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_2   (0x04UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_3   (0x08UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_4   (0x10UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_5   (0x20UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_6   (0x40UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_7   (0x80UL << TIM_BDTR_DTG_Pos)

#define TIM_BDTR_LOCK_Pos (8U)
#define TIM_BDTR_LOCK_Msk (0x3UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_LOCK     TIM_BDTR_LOCK_Msk
#define TIM_BDTR_LOCK_0   (0x1UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_LOCK_1   (0x2UL << TIM_BDTR_LOCK_Pos)

#define TIM_BDTR_OSSI_Pos (10U)
#define TIM_BDTR_OSSI_Msk (0x1UL << TIM_BDTR_OSSI_Pos)
#define TIM_BDTR_OSSI     TIM_BDTR_OSSI_Msk
#define TIM_BDTR_OSSR_Pos (11U)
#define TIM_BDTR_OSSR_Msk (0x1UL << TIM_BDTR_OSSR_Pos)
#define TIM_BDTR_OSSR     TIM_BDTR_OSSR_Msk
#define TIM_BDTR_BKE_Pos  (12U)
#define TIM_BDTR_BKE_Msk  (0x1UL << TIM_BDTR_BKE_Pos)
#define TIM_BDTR_BKE      TIM_BDTR_BKE_Msk
#define TIM_BDTR_BKP_Pos  (13U)
#define TIM_BDTR_BKP_Msk  (0x1UL << TIM_BDTR_BKP_Pos)
#define TIM_BDTR_BKP      TIM_BDTR_BKP_Msk
#define TIM_BDTR_AOE_Pos  (14U)
#define TIM_BDTR_AOE_Msk  (0x1UL << TIM_BDTR_AOE_Pos)
#define TIM_BDTR_AOE      TIM_BDTR_AOE_Msk
#define TIM_BDTR_MOE_Pos  (15U)
#define TIM_BDTR_MOE_Msk  (0x1UL << TIM_BDTR_MOE_Pos)
#define TIM_BDTR_MOE      TIM_BDTR_MOE_Msk

#define TIM_BDTR_BKF_Pos  (16U)
#define TIM_BDTR_BKF_Msk  (0xFUL << TIM_BDTR_BKF_Pos)
#define TIM_BDTR_BKF      TIM_BDTR_BKF_Msk
#define TIM_BDTR_BK2F_Pos (20U)
#define TIM_BDTR_BK2F_Msk (0xFUL << TIM_BDTR_BK2F_Pos)
#define TIM_BDTR_BK2F     TIM_BDTR_BK2F_Msk

#define TIM_BDTR_BK2E_Pos (24U)
#define TIM_BDTR_BK2E_Msk (0x1UL << TIM_BDTR_BK2E_Pos)
#define TIM_BDTR_BK2E     TIM_BDTR_BK2E_Msk
#define TIM_BDTR_BK2P_Pos (25U)
#define TIM_BDTR_BK2P_Msk (0x1UL << TIM_BDTR_BK2P_Pos)
#define TIM_BDTR_BK2P     TIM_BDTR_BK2P_Msk

/*******************  Bit definition for TIM_DCR register  ********************/
#define TIM_DCR_DBA_Pos (0U)
#define TIM_DCR_DBA_Msk (0x1FUL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA     TIM_DCR_DBA_Msk
#define TIM_DCR_DBA_0   (0x01UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_1   (0x02UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_2   (0x04UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_3   (0x08UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_4   (0x10UL << TIM_DCR_DBA_Pos)

#define TIM_DCR_DBL_Pos (8U)
#define TIM_DCR_DBL_Msk (0x1FUL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL     TIM_DCR_DBL_Msk
#define TIM_DCR_DBL_0   (0x01UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_1   (0x02UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_2   (0x04UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_3   (0x08UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_4   (0x10UL << TIM_DCR_DBL_Pos)

/*******************  Bit definition for TIM_DMAR register  *******************/
#define TIM_DMAR_DMAB_Pos (0U)
#define TIM_DMAR_DMAB_Msk (0xFFFFUL << TIM_DMAR_DMAB_Pos)
#define TIM_DMAR_DMAB     TIM_DMAR_DMAB_Msk

/*******************  Bit definition for TIM16_OR register  *******************/
#define TIM16_OR_TI1_RMP_Pos (0U)
#define TIM16_OR_TI1_RMP_Msk (0x3UL << TIM16_OR_TI1_RMP_Pos)
#define TIM16_OR_TI1_RMP     TIM16_OR_TI1_RMP_Msk
#define TIM16_OR_TI1_RMP_0   (0x1UL << TIM16_OR_TI1_RMP_Pos)
#define TIM16_OR_TI1_RMP_1   (0x2UL << TIM16_OR_TI1_RMP_Pos)

/*******************  Bit definition for TIM1_OR register  *****************
#define TIM1_OR_ETR_RMP_Pos      (0U)
#define TIM1_OR_ETR_RMP_Msk      (0xFUL << TIM1_OR_ETR_RMP_Pos)
#define TIM1_OR_ETR_RMP          TIM1_OR_ETR_RMP_Msk
#define TIM1_OR_ETR_RMP_0        (0x1UL << TIM1_OR_ETR_RMP_Pos)
#define TIM1_OR_ETR_RMP_1        (0x2UL << TIM1_OR_ETR_RMP_Pos)
#define TIM1_OR_ETR_RMP_2        (0x4UL << TIM1_OR_ETR_RMP_Pos)
#define TIM1_OR_ETR_RMP_3        (0x8UL << TIM1_OR_ETR_RMP_Pos)

/******************  Bit definition for TIM_CCMR3 register  *******************/
#define TIM_CCMR3_OC5FE_Pos (2U)
#define TIM_CCMR3_OC5FE_Msk (0x1UL << TIM_CCMR3_OC5FE_Pos)
#define TIM_CCMR3_OC5FE     TIM_CCMR3_OC5FE_Msk
#define TIM_CCMR3_OC5PE_Pos (3U)
#define TIM_CCMR3_OC5PE_Msk (0x1UL << TIM_CCMR3_OC5PE_Pos)
#define TIM_CCMR3_OC5PE     TIM_CCMR3_OC5PE_Msk

#define TIM_CCMR3_OC5M_Pos (4U)
#define TIM_CCMR3_OC5M_Msk (0x1007UL << TIM_CCMR3_OC5M_Pos)
#define TIM_CCMR3_OC5M     TIM_CCMR3_OC5M_Msk
#define TIM_CCMR3_OC5M_0   (0x0001UL << TIM_CCMR3_OC5M_Pos)
#define TIM_CCMR3_OC5M_1   (0x0002UL << TIM_CCMR3_OC5M_Pos)
#define TIM_CCMR3_OC5M_2   (0x0004UL << TIM_CCMR3_OC5M_Pos)
#define TIM_CCMR3_OC5M_3   (0x1000UL << TIM_CCMR3_OC5M_Pos)

#define TIM_CCMR3_OC5CE_Pos (7U)
#define TIM_CCMR3_OC5CE_Msk (0x1UL << TIM_CCMR3_OC5CE_Pos)
#define TIM_CCMR3_OC5CE     TIM_CCMR3_OC5CE_Msk

#define TIM_CCMR3_OC6FE_Pos (10U)
#define TIM_CCMR3_OC6FE_Msk (0x1UL << TIM_CCMR3_OC6FE_Pos)
#define TIM_CCMR3_OC6FE     TIM_CCMR3_OC6FE_Msk
#define TIM_CCMR3_OC6PE_Pos (11U)
#define TIM_CCMR3_OC6PE_Msk (0x1UL << TIM_CCMR3_OC6PE_Pos)
#define TIM_CCMR3_OC6PE     TIM_CCMR3_OC6PE_Msk

#define TIM_CCMR3_OC6M_Pos (12U)
#define TIM_CCMR3_OC6M_Msk (0x1007UL << TIM_CCMR3_OC6M_Pos)
#define TIM_CCMR3_OC6M     TIM_CCMR3_OC6M_Msk
#define TIM_CCMR3_OC6M_0   (0x0001UL << TIM_CCMR3_OC6M_Pos)
#define TIM_CCMR3_OC6M_1   (0x0002UL << TIM_CCMR3_OC6M_Pos)
#define TIM_CCMR3_OC6M_2   (0x0004UL << TIM_CCMR3_OC6M_Pos)
#define TIM_CCMR3_OC6M_3   (0x1000UL << TIM_CCMR3_OC6M_Pos)

#define TIM_CCMR3_OC6CE_Pos (15U)
#define TIM_CCMR3_OC6CE_Msk (0x1UL << TIM_CCMR3_OC6CE_Pos)
#define TIM_CCMR3_OC6CE     TIM_CCMR3_OC6CE_Msk

/******************  Bit definition for USART_CR1 register  *******************/
#define USART_CR1_UE_Pos     (0U)
#define USART_CR1_UE_Msk     (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_UE         USART_CR1_UE_Msk
#define USART_CR1_UESM_Pos   (1U)
#define USART_CR1_UESM_Msk   (0x1UL << USART_CR1_UESM_Pos)
#define USART_CR1_UESM       USART_CR1_UESM_Msk
#define USART_CR1_RE_Pos     (2U)
#define USART_CR1_RE_Msk     (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_RE         USART_CR1_RE_Msk
#define USART_CR1_TE_Pos     (3U)
#define USART_CR1_TE_Msk     (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE         USART_CR1_TE_Msk
#define USART_CR1_IDLEIE_Pos (4U)
#define USART_CR1_IDLEIE_Msk (0x1UL << USART_CR1_IDLEIE_Pos)
#define USART_CR1_IDLEIE     USART_CR1_IDLEIE_Msk
#define USART_CR1_RXNEIE_Pos (5U)
#define USART_CR1_RXNEIE_Msk (0x1UL << USART_CR1_RXNEIE_Pos)
#define USART_CR1_RXNEIE     USART_CR1_RXNEIE_Msk
#define USART_CR1_TCIE_Pos   (6U)
#define USART_CR1_TCIE_Msk   (0x1UL << USART_CR1_TCIE_Pos)
#define USART_CR1_TCIE       USART_CR1_TCIE_Msk
#define USART_CR1_TXEIE_Pos  (7U)
#define USART_CR1_TXEIE_Msk  (0x1UL << USART_CR1_TXEIE_Pos)
#define USART_CR1_TXEIE      USART_CR1_TXEIE_Msk
#define USART_CR1_PEIE_Pos   (8U)
#define USART_CR1_PEIE_Msk   (0x1UL << USART_CR1_PEIE_Pos)
#define USART_CR1_PEIE       USART_CR1_PEIE_Msk
#define USART_CR1_PS_Pos     (9U)
#define USART_CR1_PS_Msk     (0x1UL << USART_CR1_PS_Pos)
#define USART_CR1_PS         USART_CR1_PS_Msk
#define USART_CR1_PCE_Pos    (10U)
#define USART_CR1_PCE_Msk    (0x1UL << USART_CR1_PCE_Pos)
#define USART_CR1_PCE        USART_CR1_PCE_Msk
#define USART_CR1_WAKE_Pos   (11U)
#define USART_CR1_WAKE_Msk   (0x1UL << USART_CR1_WAKE_Pos)
#define USART_CR1_WAKE       USART_CR1_WAKE_Msk
#define USART_CR1_M0_Pos     (12U)
#define USART_CR1_M0_Msk     (0x1UL << USART_CR1_M0_Pos)
#define USART_CR1_M0         USART_CR1_M0_Msk
#define USART_CR1_MME_Pos    (13U)
#define USART_CR1_MME_Msk    (0x1UL << USART_CR1_MME_Pos)
#define USART_CR1_MME        USART_CR1_MME_Msk
#define USART_CR1_CMIE_Pos   (14U)
#define USART_CR1_CMIE_Msk   (0x1UL << USART_CR1_CMIE_Pos)
#define USART_CR1_CMIE       USART_CR1_CMIE_Msk
#define USART_CR1_OVER8_Pos  (15U)
#define USART_CR1_OVER8_Msk  (0x1UL << USART_CR1_OVER8_Pos)
#define USART_CR1_OVER8      USART_CR1_OVER8_Msk
#define USART_CR1_DEDT_Pos   (16U)
#define USART_CR1_DEDT_Msk   (0x1FUL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEDT       USART_CR1_DEDT_Msk
#define USART_CR1_DEDT_0     (0x01UL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEDT_1     (0x02UL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEDT_2     (0x04UL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEDT_3     (0x08UL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEDT_4     (0x10UL << USART_CR1_DEDT_Pos)
#define USART_CR1_DEAT_Pos   (21U)
#define USART_CR1_DEAT_Msk   (0x1FUL << USART_CR1_DEAT_Pos)
#define USART_CR1_DEAT       USART_CR1_DEAT_Msk
#define USART_CR1_DEAT_0     (0x01UL << USART_CR1_DEAT_Pos)
#define USART_CR1_DEAT_1     (0x02UL << USART_CR1_DEAT_Pos)
#define USART_CR1_DEAT_2     (0x04UL << USART_CR1_DEAT_Pos)
#define USART_CR1_DEAT_3     (0x08UL << USART_CR1_DEAT_Pos)
#define USART_CR1_DEAT_4     (0x10UL << USART_CR1_DEAT_Pos)
#define USART_CR1_RTOIE_Pos  (26U)
#define USART_CR1_RTOIE_Msk  (0x1UL << USART_CR1_RTOIE_Pos)
#define USART_CR1_RTOIE      USART_CR1_RTOIE_Msk
#define USART_CR1_EOBIE_Pos  (27U)
#define USART_CR1_EOBIE_Msk  (0x1UL << USART_CR1_EOBIE_Pos)
#define USART_CR1_EOBIE      USART_CR1_EOBIE_Msk
#define USART_CR1_M1_Pos     (28U)
#define USART_CR1_M1_Msk     (0x1UL << USART_CR1_M1_Pos)
#define USART_CR1_M1         USART_CR1_M1_Msk
#define USART_CR1_M_Pos      (12U)
#define USART_CR1_M_Msk      (0x10001UL << USART_CR1_M_Pos)
#define USART_CR1_M          USART_CR1_M_Msk

/******************  Bit definition for USART_CR2 register  *******************/
#define USART_CR2_ADDM7_Pos    (4U)
#define USART_CR2_ADDM7_Msk    (0x1UL << USART_CR2_ADDM7_Pos)
#define USART_CR2_ADDM7        USART_CR2_ADDM7_Msk
#define USART_CR2_LBDL_Pos     (5U)
#define USART_CR2_LBDL_Msk     (0x1UL << USART_CR2_LBDL_Pos)
#define USART_CR2_LBDL         USART_CR2_LBDL_Msk
#define USART_CR2_LBDIE_Pos    (6U)
#define USART_CR2_LBDIE_Msk    (0x1UL << USART_CR2_LBDIE_Pos)
#define USART_CR2_LBDIE        USART_CR2_LBDIE_Msk
#define USART_CR2_LBCL_Pos     (8U)
#define USART_CR2_LBCL_Msk     (0x1UL << USART_CR2_LBCL_Pos)
#define USART_CR2_LBCL         USART_CR2_LBCL_Msk
#define USART_CR2_CPHA_Pos     (9U)
#define USART_CR2_CPHA_Msk     (0x1UL << USART_CR2_CPHA_Pos)
#define USART_CR2_CPHA         USART_CR2_CPHA_Msk
#define USART_CR2_CPOL_Pos     (10U)
#define USART_CR2_CPOL_Msk     (0x1UL << USART_CR2_CPOL_Pos)
#define USART_CR2_CPOL         USART_CR2_CPOL_Msk
#define USART_CR2_CLKEN_Pos    (11U)
#define USART_CR2_CLKEN_Msk    (0x1UL << USART_CR2_CLKEN_Pos)
#define USART_CR2_CLKEN        USART_CR2_CLKEN_Msk
#define USART_CR2_STOP_Pos     (12U)
#define USART_CR2_STOP_Msk     (0x3UL << USART_CR2_STOP_Pos)
#define USART_CR2_STOP         USART_CR2_STOP_Msk
#define USART_CR2_STOP_0       (0x1UL << USART_CR2_STOP_Pos)
#define USART_CR2_STOP_1       (0x2UL << USART_CR2_STOP_Pos)
#define USART_CR2_LINEN_Pos    (14U)
#define USART_CR2_LINEN_Msk    (0x1UL << USART_CR2_LINEN_Pos)
#define USART_CR2_LINEN        USART_CR2_LINEN_Msk
#define USART_CR2_SWAP_Pos     (15U)
#define USART_CR2_SWAP_Msk     (0x1UL << USART_CR2_SWAP_Pos)
#define USART_CR2_SWAP         USART_CR2_SWAP_Msk
#define USART_CR2_RXINV_Pos    (16U)
#define USART_CR2_RXINV_Msk    (0x1UL << USART_CR2_RXINV_Pos)
#define USART_CR2_RXINV        USART_CR2_RXINV_Msk
#define USART_CR2_TXINV_Pos    (17U)
#define USART_CR2_TXINV_Msk    (0x1UL << USART_CR2_TXINV_Pos)
#define USART_CR2_TXINV        USART_CR2_TXINV_Msk
#define USART_CR2_DATAINV_Pos  (18U)
#define USART_CR2_DATAINV_Msk  (0x1UL << USART_CR2_DATAINV_Pos)
#define USART_CR2_DATAINV      USART_CR2_DATAINV_Msk
#define USART_CR2_MSBFIRST_Pos (19U)
#define USART_CR2_MSBFIRST_Msk (0x1UL << USART_CR2_MSBFIRST_Pos)
#define USART_CR2_MSBFIRST     USART_CR2_MSBFIRST_Msk
#define USART_CR2_ABREN_Pos    (20U)
#define USART_CR2_ABREN_Msk    (0x1UL << USART_CR2_ABREN_Pos)
#define USART_CR2_ABREN        USART_CR2_ABREN_Msk
#define USART_CR2_ABRMODE_Pos  (21U)
#define USART_CR2_ABRMODE_Msk  (0x3UL << USART_CR2_ABRMODE_Pos)
#define USART_CR2_ABRMODE      USART_CR2_ABRMODE_Msk
#define USART_CR2_ABRMODE_0    (0x1UL << USART_CR2_ABRMODE_Pos)
#define USART_CR2_ABRMODE_1    (0x2UL << USART_CR2_ABRMODE_Pos)
#define USART_CR2_RTOEN_Pos    (23U)
#define USART_CR2_RTOEN_Msk    (0x1UL << USART_CR2_RTOEN_Pos)
#define USART_CR2_RTOEN        USART_CR2_RTOEN_Msk
#define USART_CR2_ADD_Pos      (24U)
#define USART_CR2_ADD_Msk      (0xFFUL << USART_CR2_ADD_Pos)
#define USART_CR2_ADD          USART_CR2_ADD_Msk

/******************  Bit definition for USART_CR3 register  *******************/
#define USART_CR3_EIE_Pos     (0U)
#define USART_CR3_EIE_Msk     (0x1UL << USART_CR3_EIE_Pos)
#define USART_CR3_EIE         USART_CR3_EIE_Msk
#define USART_CR3_IREN_Pos    (1U)
#define USART_CR3_IREN_Msk    (0x1UL << USART_CR3_IREN_Pos)
#define USART_CR3_IREN        USART_CR3_IREN_Msk
#define USART_CR3_IRLP_Pos    (2U)
#define USART_CR3_IRLP_Msk    (0x1UL << USART_CR3_IRLP_Pos)
#define USART_CR3_IRLP        USART_CR3_IRLP_Msk
#define USART_CR3_HDSEL_Pos   (3U)
#define USART_CR3_HDSEL_Msk   (0x1UL << USART_CR3_HDSEL_Pos)
#define USART_CR3_HDSEL       USART_CR3_HDSEL_Msk
#define USART_CR3_NACK_Pos    (4U)
#define USART_CR3_NACK_Msk    (0x1UL << USART_CR3_NACK_Pos)
#define USART_CR3_NACK        USART_CR3_NACK_Msk
#define USART_CR3_SCEN_Pos    (5U)
#define USART_CR3_SCEN_Msk    (0x1UL << USART_CR3_SCEN_Pos)
#define USART_CR3_SCEN        USART_CR3_SCEN_Msk
#define USART_CR3_DMAR_Pos    (6U)
#define USART_CR3_DMAR_Msk    (0x1UL << USART_CR3_DMAR_Pos)
#define USART_CR3_DMAR        USART_CR3_DMAR_Msk
#define USART_CR3_DMAT_Pos    (7U)
#define USART_CR3_DMAT_Msk    (0x1UL << USART_CR3_DMAT_Pos)
#define USART_CR3_DMAT        USART_CR3_DMAT_Msk
#define USART_CR3_RTSE_Pos    (8U)
#define USART_CR3_RTSE_Msk    (0x1UL << USART_CR3_RTSE_Pos)
#define USART_CR3_RTSE        USART_CR3_RTSE_Msk
#define USART_CR3_CTSE_Pos    (9U)
#define USART_CR3_CTSE_Msk    (0x1UL << USART_CR3_CTSE_Pos)
#define USART_CR3_CTSE        USART_CR3_CTSE_Msk
#define USART_CR3_CTSIE_Pos   (10U)
#define USART_CR3_CTSIE_Msk   (0x1UL << USART_CR3_CTSIE_Pos)
#define USART_CR3_CTSIE       USART_CR3_CTSIE_Msk
#define USART_CR3_ONEBIT_Pos  (11U)
#define USART_CR3_ONEBIT_Msk  (0x1UL << USART_CR3_ONEBIT_Pos)
#define USART_CR3_ONEBIT      USART_CR3_ONEBIT_Msk
#define USART_CR3_OVRDIS_Pos  (12U)
#define USART_CR3_OVRDIS_Msk  (0x1UL << USART_CR3_OVRDIS_Pos)
#define USART_CR3_OVRDIS      USART_CR3_OVRDIS_Msk
#define USART_CR3_DDRE_Pos    (13U)
#define USART_CR3_DDRE_Msk    (0x1UL << USART_CR3_DDRE_Pos)
#define USART_CR3_DDRE        USART_CR3_DDRE_Msk
#define USART_CR3_DEM_Pos     (14U)
#define USART_CR3_DEM_Msk     (0x1UL << USART_CR3_DEM_Pos)
#define USART_CR3_DEM         USART_CR3_DEM_Msk
#define USART_CR3_DEP_Pos     (15U)
#define USART_CR3_DEP_Msk     (0x1UL << USART_CR3_DEP_Pos)
#define USART_CR3_DEP         USART_CR3_DEP_Msk
#define USART_CR3_SCARCNT_Pos (17U)
#define USART_CR3_SCARCNT_Msk (0x7UL << USART_CR3_SCARCNT_Pos)
#define USART_CR3_SCARCNT     USART_CR3_SCARCNT_Msk
#define USART_CR3_SCARCNT_0   (0x1UL << USART_CR3_SCARCNT_Pos)
#define USART_CR3_SCARCNT_1   (0x2UL << USART_CR3_SCARCNT_Pos)
#define USART_CR3_SCARCNT_2   (0x4UL << USART_CR3_SCARCNT_Pos)
#define USART_CR3_WUS_Pos     (20U)
#define USART_CR3_WUS_Msk     (0x3UL << USART_CR3_WUS_Pos)
#define USART_CR3_WUS         USART_CR3_WUS_Msk
#define USART_CR3_WUS_0       (0x1UL << USART_CR3_WUS_Pos)
#define USART_CR3_WUS_1       (0x2UL << USART_CR3_WUS_Pos)
#define USART_CR3_WUFIE_Pos   (22U)
#define USART_CR3_WUFIE_Msk   (0x1UL << USART_CR3_WUFIE_Pos)
#define USART_CR3_WUFIE       USART_CR3_WUFIE_Msk

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_FRACTION_Pos (0U)
#define USART_BRR_DIV_FRACTION_Msk (0xFUL << USART_BRR_DIV_FRACTION_Pos)
#define USART_BRR_DIV_FRACTION     USART_BRR_DIV_FRACTION_Msk
#define USART_BRR_DIV_MANTISSA_Pos (4U)
#define USART_BRR_DIV_MANTISSA_Msk (0xFFFUL << USART_BRR_DIV_MANTISSA_Pos)
#define USART_BRR_DIV_MANTISSA     USART_BRR_DIV_MANTISSA_Msk

/******************  Bit definition for USART_GTPR register  ******************/
#define USART_GTPR_PSC_Pos (0U)
#define USART_GTPR_PSC_Msk (0xFFUL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC     USART_GTPR_PSC_Msk
#define USART_GTPR_GT_Pos  (8U)
#define USART_GTPR_GT_Msk  (0xFFUL << USART_GTPR_GT_Pos)
#define USART_GTPR_GT      USART_GTPR_GT_Msk

/*******************  Bit definition for USART_RTOR register  *****************/
#define USART_RTOR_RTO_Pos  (0U)
#define USART_RTOR_RTO_Msk  (0xFFFFFFUL << USART_RTOR_RTO_Pos)
#define USART_RTOR_RTO      USART_RTOR_RTO_Msk
#define USART_RTOR_BLEN_Pos (24U)
#define USART_RTOR_BLEN_Msk (0xFFUL << USART_RTOR_BLEN_Pos)
#define USART_RTOR_BLEN     USART_RTOR_BLEN_Msk

/*******************  Bit definition for USART_RQR register  ******************/
#define USART_RQR_ABRRQ_Pos (0U)
#define USART_RQR_ABRRQ_Msk (0x1UL << USART_RQR_ABRRQ_Pos)
#define USART_RQR_ABRRQ     USART_RQR_ABRRQ_Msk
#define USART_RQR_SBKRQ_Pos (1U)
#define USART_RQR_SBKRQ_Msk (0x1UL << USART_RQR_SBKRQ_Pos)
#define USART_RQR_SBKRQ     USART_RQR_SBKRQ_Msk
#define USART_RQR_MMRQ_Pos  (2U)
#define USART_RQR_MMRQ_Msk  (0x1UL << USART_RQR_MMRQ_Pos)
#define USART_RQR_MMRQ      USART_RQR_MMRQ_Msk
#define USART_RQR_RXFRQ_Pos (3U)
#define USART_RQR_RXFRQ_Msk (0x1UL << USART_RQR_RXFRQ_Pos)
#define USART_RQR_RXFRQ     USART_RQR_RXFRQ_Msk
#define USART_RQR_TXFRQ_Pos (4U)
#define USART_RQR_TXFRQ_Msk (0x1UL << USART_RQR_TXFRQ_Pos)
#define USART_RQR_TXFRQ     USART_RQR_TXFRQ_Msk

/*******************  Bit definition for USART_ISR register  ******************/
#define USART_ISR_PE_Pos    (0U)
#define USART_ISR_PE_Msk    (0x1UL << USART_ISR_PE_Pos)
#define USART_ISR_PE        USART_ISR_PE_Msk
#define USART_ISR_FE_Pos    (1U)
#define USART_ISR_FE_Msk    (0x1UL << USART_ISR_FE_Pos)
#define USART_ISR_FE        USART_ISR_FE_Msk
#define USART_ISR_NE_Pos    (2U)
#define USART_ISR_NE_Msk    (0x1UL << USART_ISR_NE_Pos)
#define USART_ISR_NE        USART_ISR_NE_Msk
#define USART_ISR_ORE_Pos   (3U)
#define USART_ISR_ORE_Msk   (0x1UL << USART_ISR_ORE_Pos)
#define USART_ISR_ORE       USART_ISR_ORE_Msk
#define USART_ISR_IDLE_Pos  (4U)
#define USART_ISR_IDLE_Msk  (0x1UL << USART_ISR_IDLE_Pos)
#define USART_ISR_IDLE      USART_ISR_IDLE_Msk
#define USART_ISR_RXNE_Pos  (5U)
#define USART_ISR_RXNE_Msk  (0x1UL << USART_ISR_RXNE_Pos)
#define USART_ISR_RXNE      USART_ISR_RXNE_Msk
#define USART_ISR_TC_Pos    (6U)
#define USART_ISR_TC_Msk    (0x1UL << USART_ISR_TC_Pos)
#define USART_ISR_TC        USART_ISR_TC_Msk
#define USART_ISR_TXE_Pos   (7U)
#define USART_ISR_TXE_Msk   (0x1UL << USART_ISR_TXE_Pos)
#define USART_ISR_TXE       USART_ISR_TXE_Msk
#define USART_ISR_LBDF_Pos  (8U)
#define USART_ISR_LBDF_Msk  (0x1UL << USART_ISR_LBDF_Pos)
#define USART_ISR_LBDF      USART_ISR_LBDF_Msk
#define USART_ISR_CTSIF_Pos (9U)
#define USART_ISR_CTSIF_Msk (0x1UL << USART_ISR_CTSIF_Pos)
#define USART_ISR_CTSIF     USART_ISR_CTSIF_Msk
#define USART_ISR_CTS_Pos   (10U)
#define USART_ISR_CTS_Msk   (0x1UL << USART_ISR_CTS_Pos)
#define USART_ISR_CTS       USART_ISR_CTS_Msk
#define USART_ISR_RTOF_Pos  (11U)
#define USART_ISR_RTOF_Msk  (0x1UL << USART_ISR_RTOF_Pos)
#define USART_ISR_RTOF      USART_ISR_RTOF_Msk
#define USART_ISR_EOBF_Pos  (12U)
#define USART_ISR_EOBF_Msk  (0x1UL << USART_ISR_EOBF_Pos)
#define USART_ISR_EOBF      USART_ISR_EOBF_Msk
#define USART_ISR_ABRE_Pos  (14U)
#define USART_ISR_ABRE_Msk  (0x1UL << USART_ISR_ABRE_Pos)
#define USART_ISR_ABRE      USART_ISR_ABRE_Msk
#define USART_ISR_ABRF_Pos  (15U)
#define USART_ISR_ABRF_Msk  (0x1UL << USART_ISR_ABRF_Pos)
#define USART_ISR_ABRF      USART_ISR_ABRF_Msk
#define USART_ISR_BUSY_Pos  (16U)
#define USART_ISR_BUSY_Msk  (0x1UL << USART_ISR_BUSY_Pos)
#define USART_ISR_BUSY      USART_ISR_BUSY_Msk
#define USART_ISR_CMF_Pos   (17U)
#define USART_ISR_CMF_Msk   (0x1UL << USART_ISR_CMF_Pos)
#define USART_ISR_CMF       USART_ISR_CMF_Msk
#define USART_ISR_SBKF_Pos  (18U)
#define USART_ISR_SBKF_Msk  (0x1UL << USART_ISR_SBKF_Pos)
#define USART_ISR_SBKF      USART_ISR_SBKF_Msk
#define USART_ISR_RWU_Pos   (19U)
#define USART_ISR_RWU_Msk   (0x1UL << USART_ISR_RWU_Pos)
#define USART_ISR_RWU       USART_ISR_RWU_Msk
#define USART_ISR_WUF_Pos   (20U)
#define USART_ISR_WUF_Msk   (0x1UL << USART_ISR_WUF_Pos)
#define USART_ISR_WUF       USART_ISR_WUF_Msk
#define USART_ISR_TEACK_Pos (21U)
#define USART_ISR_TEACK_Msk (0x1UL << USART_ISR_TEACK_Pos)
#define USART_ISR_TEACK     USART_ISR_TEACK_Msk
#define USART_ISR_REACK_Pos (22U)
#define USART_ISR_REACK_Msk (0x1UL << USART_ISR_REACK_Pos)
#define USART_ISR_REACK     USART_ISR_REACK_Msk

/*******************  Bit definition for USART_ICR register  ******************/
#define USART_ICR_PECF_Pos   (0U)
#define USART_ICR_PECF_Msk   (0x1UL << USART_ICR_PECF_Pos)
#define USART_ICR_PECF       USART_ICR_PECF_Msk
#define USART_ICR_FECF_Pos   (1U)
#define USART_ICR_FECF_Msk   (0x1UL << USART_ICR_FECF_Pos)
#define USART_ICR_FECF       USART_ICR_FECF_Msk
#define USART_ICR_NCF_Pos    (2U)
#define USART_ICR_NCF_Msk    (0x1UL << USART_ICR_NCF_Pos)
#define USART_ICR_NCF        USART_ICR_NCF_Msk
#define USART_ICR_ORECF_Pos  (3U)
#define USART_ICR_ORECF_Msk  (0x1UL << USART_ICR_ORECF_Pos)
#define USART_ICR_ORECF      USART_ICR_ORECF_Msk
#define USART_ICR_IDLECF_Pos (4U)
#define USART_ICR_IDLECF_Msk (0x1UL << USART_ICR_IDLECF_Pos)
#define USART_ICR_IDLECF     USART_ICR_IDLECF_Msk
#define USART_ICR_TCCF_Pos   (6U)
#define USART_ICR_TCCF_Msk   (0x1UL << USART_ICR_TCCF_Pos)
#define USART_ICR_TCCF       USART_ICR_TCCF_Msk
#define USART_ICR_LBDCF_Pos  (8U)
#define USART_ICR_LBDCF_Msk  (0x1UL << USART_ICR_LBDCF_Pos)
#define USART_ICR_LBDCF      USART_ICR_LBDCF_Msk
#define USART_ICR_CTSCF_Pos  (9U)
#define USART_ICR_CTSCF_Msk  (0x1UL << USART_ICR_CTSCF_Pos)
#define USART_ICR_CTSCF      USART_ICR_CTSCF_Msk
#define USART_ICR_RTOCF_Pos  (11U)
#define USART_ICR_RTOCF_Msk  (0x1UL << USART_ICR_RTOCF_Pos)
#define USART_ICR_RTOCF      USART_ICR_RTOCF_Msk
#define USART_ICR_EOBCF_Pos  (12U)
#define USART_ICR_EOBCF_Msk  (0x1UL << USART_ICR_EOBCF_Pos)
#define USART_ICR_EOBCF      USART_ICR_EOBCF_Msk
#define USART_ICR_CMCF_Pos   (17U)
#define USART_ICR_CMCF_Msk   (0x1UL << USART_ICR_CMCF_Pos)
#define USART_ICR_CMCF       USART_ICR_CMCF_Msk
#define USART_ICR_WUCF_Pos   (20U)
#define USART_ICR_WUCF_Msk   (0x1UL << USART_ICR_WUCF_Pos)
#define USART_ICR_WUCF       USART_ICR_WUCF_Msk

/*******************  Bit definition for USART_RDR register  ******************/
#define USART_RDR_RDR_Pos (0U)
#define USART_RDR_RDR_Msk (0x1FFUL << USART_RDR_RDR_Pos)
#define USART_RDR_RDR     USART_RDR_RDR_Msk

/*******************  Bit definition for USART_TDR register  ******************/
#define USART_TDR_TDR_Pos (0U)
#define USART_TDR_TDR_Msk (0x1FFUL << USART_TDR_TDR_Pos)
#define USART_TDR_TDR     USART_TDR_TDR_Msk

#endif