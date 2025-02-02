#include "spi.h"
#include "stm32f3xx.h"
#include "unity.h"

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_enable_clock_access_to_gpiob(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BITS_HIGH(RCC_AHBENR_GPIOBEN_Msk, RCC->AHBENR);
}

void
should_enable_clock_access_to_spi1(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BITS_HIGH(RCC_APB2ENR_SPI1EN, RCC->APB2ENR);
}

void
should_set_gpio_to_spi_alternate_function(void)
{
    // when
    spi_init_master();

    // then
    TEST_ASSERT_BITS_HIGH(GPIO_MODER_MODER3_1, GPIOB->MODER);
    TEST_ASSERT_BITS_LOW(GPIO_MODER_MODER3_0, GPIOB->MODER);
    TEST_ASSERT_BITS_HIGH((5 << GPIO_AFRL_AFRL3_Pos), GPIOB->AFR[0]);

    TEST_ASSERT_BITS_HIGH(GPIO_MODER_MODER4_1, GPIOB->MODER);
    TEST_ASSERT_BITS_LOW(GPIO_MODER_MODER4_0, GPIOB->MODER);
    TEST_ASSERT_BITS_HIGH((5 << GPIO_AFRL_AFRL4_Pos), GPIOB->AFR[0]);

    TEST_ASSERT_BITS_HIGH(GPIO_MODER_MODER5_1, GPIOB->MODER);
    TEST_ASSERT_BITS_LOW(GPIO_MODER_MODER5_0, GPIOB->MODER);
    TEST_ASSERT_BITS_HIGH((4 << GPIO_AFRL_AFRL5_Pos), GPIOB->AFR[0]);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_enable_clock_access_to_gpiob);
    RUN_TEST(should_enable_clock_access_to_spi1);
    RUN_TEST(should_set_gpio_to_spi_alternate_function);
    return UNITY_END();
}