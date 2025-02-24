#include "adc.h"
#include <stdbool.h>
#include <stm32f3xx.h>
#include <string.h>

#define SEQ_SIZE 2

typedef struct adc_periph
{
    uint16_t value[SEQ_SIZE];
    uint8_t index;
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

void
adc_init()
{
    adc_peripheral.index = 0;

    init_gpio();

    // enable clock access to ADC
    RCC->AHBENR = RCC_AHBENR_ADC12EN;

    // Set ADC Clock Source (Use AHB clock)
    ADC12_COMMON->CCR &= ~ADC_CCR_CKMODE;  // Clear clock mode bits
    ADC12_COMMON->CCR |= ADC_CCR_CKMODE_0; // Set ADC clock to HCLK/1

    advreg_enable();
    init_adc_sequence();

    // enable adc continous conversion mode
    ADC1->CFGR |= ADC_CFGR_CONT | ADC_CFGR_AUTDLY;

    ADC1->IER |= ADC_IER_EOCIE | ADC_IER_EOSIE;

    // enable IRQ
    NVIC_EnableIRQ(ADC1_2_IRQn);
}

void
adc_on(void)
{
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY))
        ;
    ADC1->ISR |= ADC_ISR_ADRDY;
}

void
adc_off(void)
{
    adc_stop();
    ADC1->CR |= ADC_CR_ADDIS;
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
ADC1_2_IRQHandler(void)
{
    if (ADC1->ISR & ADC_ISR_EOC)
    {
        uint16_t value = ADC1->DR;
        adc_peripheral.value[adc_peripheral.index++] = value;

        // if (adc_peripheral.index >= SEQ_SIZE)
        // {
        //     adc_peripheral.index = 0;
        //     adc_sequence_complete_isr(adc_peripheral.value, SEQ_SIZE);
        // }
    }

    if (ADC1->ISR & ADC_ISR_EOS)
    {
        uint16_t value = ADC1->DR;
        adc_peripheral.value[adc_peripheral.index] = value;
        adc_peripheral.index = 0;
        adc_sequence_complete_isr(adc_peripheral.value, SEQ_SIZE);
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

    // set PA1 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER1_1 | GPIO_MODER_MODER1_0;

    // set PA3 in analog mode
    GPIOA->MODER |= GPIO_MODER_MODER3_1 | GPIO_MODER_MODER3_0;
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
    ADC1->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC1->CR |= ADC_CR_ADVREGEN_0;

    for (int i = 0; i < 8000; i++)
        ;
}

static inline void
advreg_disable()
{
    ADC1->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);
    ADC1->CR |= ADC_CR_ADVREGEN_1;
}

static inline void
init_adc_sequence(void)
{
    ADC1->SQR1 |= (1 << ADC_SQR1_L_Pos);
    ADC1->SQR1 |= (2 << ADC_SQR1_SQ1_Pos) | (4 << ADC_SQR1_SQ2_Pos);
}