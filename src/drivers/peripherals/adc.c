#include "adc.h"
#include <stdbool.h>
#include <stm32f3xx.h>
#include <string.h>

#define SEQ_SIZE 3

typedef struct adc_periph
{
    uint16_t value[SEQ_SIZE];
    uint8_t  index;
} adc_peripheral_t;

static adc_peripheral_t volatile adc_peripheral;

static inline void
init_gpio(void);

static inline void
advreg_enable(void);

static inline void
advreg_disable();

static inline void
init_adc_sequence(void);

static inline void
init_adc_sample_rates(void);

void
adc_init()
{
    adc_peripheral.index = 0;

    init_gpio();

    // enable clock access to ADC
    RCC->AHBENR |= RCC_AHBENR_ADC12EN;

    // Set ADC Clock Source (Use PLL/2 clock, resulting 8MHz)
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV2;

    advreg_enable();
    init_adc_sequence();
    init_adc_sample_rates();

    // enable adc continous conversion mode
    ADC2->CFGR |= ADC_CFGR_CONT | ADC_CFGR_AUTDLY;

    ADC2->IER |= ADC_IER_EOCIE | ADC_IER_EOSIE;

    // enable IRQ
    NVIC_EnableIRQ(ADC1_2_IRQn);
}

void
adc_on(void)
{
    ADC2->CR |= ADC_CR_ADEN;
    while (!(ADC2->ISR & ADC_ISR_ADRDY))
        ;
}

void
adc_off(void)
{
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
ADC1_2_IRQHandler(void)
{
    if (ADC2->ISR & ADC_ISR_EOC)
    {
        adc_peripheral.value[adc_peripheral.index++] = ADC2->DR;
    }

    if (ADC2->ISR & ADC_ISR_EOS)
    {
        ADC2->ISR |= ADC_ISR_EOS;
        adc_peripheral.value[adc_peripheral.index] = ADC2->DR;
        adc_peripheral.index                       = 0;
        adc_sequence_complete_isr(adc_peripheral.value, 3);
    }
}

__attribute__((weak)) void
adc_sequence_complete_isr(uint16_t volatile value[], uint8_t size)
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
advreg_enable(void)
{
    /*
     * NOTE: The reference manual says that the software must wait
     * for the regulator to start. The data sheet stands for 10 uS.
     * I omitted this and the program still works, but keep in mind
     * to add some timer polling here
     */
    ADC2->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC2->CR |= ADC_CR_ADVREGEN_0;

    for (int i = 0; i < 16000; i++)
        ;
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
    ADC2->SQR1 |= (1 << ADC_SQR1_SQ1_Pos) | (2 << ADC_SQR1_SQ2_Pos) |
                  (3 << ADC_SQR1_SQ3_Pos);
}

static inline void
init_adc_sample_rates(void)
{
    ADC2->SMPR1 |= (2 << ADC_SMPR1_SMP1_Pos) | (2 << ADC_SMPR1_SMP2_Pos) | (2 << ADC_SMPR1_SMP3_Pos);
}