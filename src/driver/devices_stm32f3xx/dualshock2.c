#include "dualshock2.h"
#include "sysclock.h"
#include <devices/dualshock2.h>
#include <errno.h>
#include <stdbool.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    GPIO_TypeDef *port;
    uint8_t       bit;
} dualshock2_gpio_t;

typedef struct
{
    uint16_t commands;
    bool volatile handled;
} dualshock2_instance_t;

POOL_DECLARE(dualshock2, dualshock2_instance_t, 1)

static dualshock2_pool_t pool;

static inline void
init_gpio(void);

static inline void
init_tim2(void);

static inline void
init_spi(void);

static inline void
init_dualshock2_instance(void);

void
dualshock2_init(void)
{
    init_gpio();
    init_tim2();
    init_spi();
    dualshock2_pool_init(&pool);
    init_dualshock2_instance();
}

int
devices_dualshock2_read(dualshock2_t h_self, uint16_t *p_commands)
{
    dualshock2_instance_t *p_self = dualshock2_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -EINVAL;
    }

    if (p_self->handled)
    {
        return RESULT_NOT_READY;
    }

    *p_commands     = p_self->commands;
    p_self->handled = true;

    return RESULT_OK;
}

static inline void
init_gpio(void)
{
    // enable clock access to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // enable clock access to GPIOF
    RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

    // set PF0 as output - DUALSHOCK2_1 SPI device select
    GPIOF->MODER |= GPIO_MODER_MODER0_0;
    GPIOF->MODER &= ~GPIO_MODER_MODER0_1;

    // set PF0 high - SPI idle state
    GPIOF->ODR |= (1 << 0);

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
}

static inline void
init_tim2(void)
{
    // set clock access to TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // set compare match every 16ms on channel 1
    TIM2->PSC  = sysclock_get_prescaller_base(1000) - 1;
    TIM2->ARR  = 16 - 1;
    TIM2->CCR1 = 16;

    // enable the timer
    TIM2->CR1 |= TIM_CR1_CEN;

    // enable capture/compare interrupt for channel 1
    TIM2->DIER |= TIM_DIER_CC1IE;

    // enable TIM2 IRQ in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);
}

static inline void
init_spi(void)
{
    // enable APB2 clock access to SPI
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // disable SPI before configuration
    SPI1->CR1 &= ~SPI_CR1_SPE;

    // set SPI bus speed to 62.5kHz (16MHz / 256psc)
    SPI1->CR1 |= (7 << SPI_CR1_BR_Pos);

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

static inline void
init_dualshock2_instance(void)
{
}

void
// cppcheck-suppress unusedFunction
TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_CC1IF)
    {
        TIM2->SR &= ~TIM_SR_CC1IF;
    }
}

void
// cppcheck-suppress unusedFunction
SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_TXE)
    {
        // transmit_byte_isr();
    }

    if (SPI1->SR & SPI_SR_RXNE)
    {
        // receive_byte_isr();
    }
}