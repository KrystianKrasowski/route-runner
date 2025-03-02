#include "adc.h"
#include "systick.h"
#include "tim6.h"
#include <stdbool.h>
#include <stm32f3xx.h>
#include <string.h>
#include <stdio.h>

uint16_t adc_buffer[ADC_BUFFER_SIZE];

static inline void
init_gpio(void);

static inline void
init_rcc(void);

static inline void
enable_advreg(void);

static inline void
advreg_disable();

static inline void
init_adc_sequence(void);

static inline void
init_tim6_trgo_trigger(void);

static inline void
init_adc_interrupts(void);

static inline void
init_adc_dma(void);

void
adc_init()
{
    init_gpio();
    init_rcc();
    enable_advreg();
    init_adc_sequence();
    init_tim6_trgo_trigger();
    init_adc_dma();
}

void
adc_on(void)
{
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
    ADC2->CR |= ADC_CR_ADDIS;
}

void
adc_start(void)
{
    ADC2->CR |= ADC_CR_ADSTART;
}

void
adc_stop(void)
{
    ADC2->CR |= ADC_CR_ADSTP;
}

void
DMA1_Channel2_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF2)
    {
        DMA1->IFCR |= DMA_IFCR_CTCIF2;
        adc_sequence_complete_isr(adc_buffer);
    }
}

__attribute__((weak)) void
adc_sequence_complete_isr(uint16_t value[])
{
}

static inline void
init_gpio(void)
{
    // enable clock access to gpioa
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // set PA4 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER4_1 | GPIO_MODER_MODER4_0;

    // set PA5 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER5_0;

    // set PA6 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER6_0;
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
    ADC2->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC2->CR |= ADC_CR_ADVREGEN_0;

    systick_delay_us(10);
}

static inline void
advreg_disable()
{
    ADC2->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC2->CR |= ADC_CR_ADVREGEN_1;
}

static inline void
init_adc_sequence(void)
{
    ADC2->SQR1 |= (2 << ADC_SQR1_L_Pos);
    ADC2->SQR1 |= (1 << ADC_SQR1_SQ1_Pos);
    ADC2->SQR1 |= (2 << ADC_SQR1_SQ2_Pos);
    ADC2->SQR1 |= (3 << ADC_SQR1_SQ3_Pos);
}

static inline void
init_tim6_trgo_trigger(void)
{
    tim6_init();
    ADC2->CFGR |= (13 << ADC_CFGR_EXTSEL_Pos);
    ADC2->CFGR |= (1 << ADC_CFGR_EXTEN_Pos);
}

static inline void
init_adc_interrupts(void)
{
    // set interrupt on conversion end
    ADC2->IER |= ADC_IER_EOCIE | ADC_IER_EOSIE;

    // enable IRQ
    NVIC_EnableIRQ(ADC1_2_IRQn);
}

static inline void
init_adc_dma(void)
{
    // enable clock access to DMA controller
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    // Set peripheral address
    DMA1_Channel2->CPAR = (uint32_t)&ADC2->DR;

    // set memory address
    DMA1_Channel2->CMAR = (uint32_t)adc_buffer;

    // set dma transfers number
    DMA1_Channel2->CNDTR = ADC_BUFFER_SIZE;

    // set memory increment mode
    DMA1_Channel2->CCR |= DMA_CCR_MINC;

    // set circular mode
    DMA1_Channel2->CCR |= DMA_CCR_CIRC;

    // set peripheral 16-bit size
    DMA1_Channel2->CCR |= (1 << DMA_CCR_PSIZE_Pos);

    // set memory 16-bit size
    DMA1_Channel2->CCR |= (1 << DMA_CCR_MSIZE_Pos);

    // Enable transfer complete interrupt
    DMA1_Channel2->CCR |= DMA_CCR_TCIE;
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);

    // Enable DMA channel
    DMA1_Channel2->CCR |= DMA_CCR_EN;

    // Enable DMA in ADC
    ADC2->CFGR |= ADC_CFGR_DMAEN | ADC_CFGR_DMACFG;
}