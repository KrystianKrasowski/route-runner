#include "adc.h"
#include "systick.h"
#include "tim6.h"
#include <stdbool.h>
#include <stm32f3xx.h>
#include <string.h>
#include <stdio.h>

uint16_t volatile adc_buffer[ADC_BUFFER_SIZE];

static inline void
init_gpio(void);

static inline void
init_rcc(void);

static inline void
enable_advreg(void);

static inline void
advreg_disable();

static inline void
init_adc_resolution(void);

static inline void
init_adc_sequence(void);

static inline void
init_tim6_trgo_trigger(void);

static inline void
init_adc_dma(void);

void
adc_init()
{
    init_rcc();
    init_gpio();
    init_adc_dma();
    enable_advreg();

    // enable ADC 12 dual mode
    ADC12_COMMON->CCR |= (6 << ADC12_CCR_MULTI_Pos);

    // enable DMA for dual mode 8-bit
    ADC12_COMMON->CCR |= (3 << ADC12_CCR_MDMA_Pos);

    // DMA circular mode
    ADC12_COMMON->CCR |= (1 << ADC12_CCR_DMACFG_Pos);

    init_adc_resolution();
    init_adc_sequence();
    init_tim6_trgo_trigger();
}

void
adc_on(void)
{
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY))
        ;

    ADC2->CR |= ADC_CR_ADEN;
    while (!(ADC2->ISR & ADC_ISR_ADRDY))
        ;

    tim6_run();
}

void
adc_off(void)
{
    tim6_stop();
    adc_stop();
    ADC1->CR |= ADC_CR_ADDIS;
    ADC2->CR |= ADC_CR_ADDIS;
}

void
adc_start(void)
{
    ADC1->CR |= ADC_CR_ADSTART;
}

void
adc_stop(void)
{
    ADC1->CR |= ADC_CR_ADSTP;
}

void
DMA1_Channel1_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        DMA1->IFCR |= DMA_IFCR_CTCIF1;
        adc_sequence_complete_isr(adc_buffer);
    }
}

static inline void
init_gpio(void)
{
    // enable clock access to gpioa
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // set PA1 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER1_1 | GPIO_MODER_MODER1_0;

    // set PA3 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER3_1 | GPIO_MODER_MODER3_0;

    // set PA4 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER4_1 | GPIO_MODER_MODER4_0;

    // set PA5 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER5_0;

    // set PA6 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER6_0;

    // set PA7 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER7_1 | GPIO_MODER_MODER7_0;
}

static inline void
init_rcc(void)
{
    // enable clock access to ADC
    RCC->AHBENR |= RCC_AHBENR_ADC12EN;

    // Set ADC Clock Source (Use PLL/2 clock, resulting 8MHz)
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2;
}

static inline void
enable_advreg(void)
{
    ADC1->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC1->CR |= ADC_CR_ADVREGEN_0;

    ADC2->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC2->CR |= ADC_CR_ADVREGEN_0;

    systick_delay_us(10);
}

static inline void
advreg_disable()
{
    ADC1->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC1->CR |= ADC_CR_ADVREGEN_1;

    ADC2->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC2->CR |= ADC_CR_ADVREGEN_1;
}

static inline void
init_adc_resolution(void)
{
    // set 8-bit resolution
    ADC1->CFGR |= (2 << ADC_CFGR_RES_Pos);
    ADC2->CFGR |= (2 << ADC_CFGR_RES_Pos);
}

static inline void
init_adc_sequence(void)
{
    ADC1->SQR1 |= (3 << ADC_SQR1_L_Pos);
    ADC1->SQR1 |= (2 << ADC_SQR1_SQ1_Pos);
    ADC1->SQR1 |= (4 << ADC_SQR1_SQ2_Pos);
    // dummy conversions for sequence length match
    ADC1->SQR1 |= (4 << ADC_SQR1_SQ3_Pos);
    ADC1->SQR1 |= (4 << ADC_SQR1_SQ4_Pos);

    ADC2->SQR1 |= (3 << ADC_SQR1_L_Pos);
    ADC2->SQR1 |= (1 << ADC_SQR1_SQ1_Pos);
    ADC2->SQR1 |= (2 << ADC_SQR1_SQ2_Pos);
    ADC2->SQR1 |= (3 << ADC_SQR1_SQ3_Pos);
    ADC2->SQR1 |= (4 << ADC_SQR1_SQ4_Pos);
}

static inline void
init_tim6_trgo_trigger(void)
{
    tim6_init();
    ADC1->CFGR |= (13 << ADC_CFGR_EXTSEL_Pos);
    ADC1->CFGR |= (1 << ADC_CFGR_EXTEN_Pos);
}

static inline void
init_adc_dma(void)
{
    // enable clock access to DMA controller
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    // Disable DMA channel - it is necessary due to compiler optimizations
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;

    // Set peripheral address
    DMA1_Channel1->CPAR = (uint32_t)&ADC12_COMMON->CDR;

    // set memory address
    DMA1_Channel1->CMAR = (uint32_t)adc_buffer;

    // set dma transfers number
    DMA1_Channel1->CNDTR = ADC_BUFFER_SIZE;

    // set memory increment mode
    DMA1_Channel1->CCR |= DMA_CCR_MINC;

    // set circular mode
    DMA1_Channel1->CCR |= DMA_CCR_CIRC;

    // set peripheral 32-bit size
    DMA1_Channel1->CCR |= (2 << DMA_CCR_PSIZE_Pos);

    // set memory 16-bit size
    DMA1_Channel1->CCR |= (1 << DMA_CCR_MSIZE_Pos);

    // Enable transfer complete interrupt
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    DMA1_Channel1->CCR |= DMA_CCR_TCIE;

    // Enable DMA channel
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}