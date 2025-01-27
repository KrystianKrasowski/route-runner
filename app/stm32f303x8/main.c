#include "stm32f3xx.h"

#define PIN5    (1U << 3)
#define LED_PIN PIN5

int
main(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER3_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER3_1;

    while (1)
    {
        GPIOB->ODR ^= LED_PIN;
        for (int i = 0; i < 100000; i++)
        {
        }
    }
}