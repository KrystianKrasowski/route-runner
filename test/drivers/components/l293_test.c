#include <gpio_mock.h>
#include <l293.h>
#include <tim3_mock.h>
#include <unity.h>
#include <unity_config.h>

void
setUp(void)
{
    gpio_mock_reset();
    tim3_mock_reset();
}

void
tearDown(void)
{
}

void
should_initialize_gpio_channels(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();

    // when
    l293_init(&l293_channel);

    // then
    TEST_ASSERT_TRUE(gpio_mock_verify_pin_init(GPIO_MOTOR_LEFT_A1));
    TEST_ASSERT_TRUE(gpio_mock_verify_pin_init(GPIO_MOTOR_LEFT_A2));
}

void
should_initialize_timer3(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();

    // when
    l293_init(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(1, tim3_mock_verify_init_calls());
}

void
should_initialize_pwm_on_timer3_channel3(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();

    // when
    l293_init(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(1, tim3_mock_verify_pwm_init_on_channel3());
}

void
should_initialize_pwm_on_timer3_channel4(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();

    // when
    l293_init(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(1, tim3_mock_verify_pwm_init_on_channel4());
}

void
should_enable_timer3(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();

    // when
    l293_init(&l293_channel);

    // then
    TEST_ASSERT_TRUE(tim3_mock_verify_enabled());
}

void
should_turn_right_the_right_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);

    // when
    l293_set_right(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_HIGH, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A2));
}

void
should_turn_right_the_left_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();
    l293_init(&l293_channel);

    // when
    l293_set_right(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_LEFT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_HIGH, gpio_mock_get_state(GPIO_MOTOR_LEFT_A2));
}

void
should_turn_left_the_right_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);

    // when
    l293_set_left(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_HIGH, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A2));
}

void
should_turn_left_the_left_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();
    l293_init(&l293_channel);

    // when
    l293_set_left(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_HIGH, gpio_mock_get_state(GPIO_MOTOR_LEFT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_LEFT_A2));
}

void
should_stop_running_left_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();
    l293_init(&l293_channel);
    l293_set_left(&l293_channel);
    l293_enable(&l293_channel);

    // when
    l293_stop_running(&l293_channel);

    // then
    TEST_ASSERT_FALSE(tim3_mock_verify_channel3_running());
}

void
should_stop_running_right_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);
    l293_set_left(&l293_channel);

    // when
    l293_stop_running(&l293_channel);

    // then
    TEST_ASSERT_FALSE(tim3_mock_verify_channel4_running());
}

void
should_stop_left_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_left();
    l293_init(&l293_channel);
    l293_set_left(&l293_channel);
    l293_enable(&l293_channel);

    // when
    l293_stop(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_LEFT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_LEFT_A2));
    TEST_ASSERT_TRUE(tim3_mock_verify_channel3_running());
}

void
should_stop_right_channel(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);
    l293_set_left(&l293_channel);
    l293_enable(&l293_channel);

    // when
    l293_stop(&l293_channel);

    // then
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A1));
    TEST_ASSERT_EQUAL(GPIO_STATE_LOW, gpio_mock_get_state(GPIO_MOTOR_RIGHT_A2));
    TEST_ASSERT_TRUE(tim3_mock_verify_channel4_running());
}

void
should_enable_pwm_signal(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);

    // when
    l293_enable(&l293_channel);

    // then
    TEST_ASSERT_TRUE(tim3_mock_verify_channel4_running());
}

void
should_disable_pwm_signal(void)
{
    // given
    l293_t l293_channel = l293_create_channel_right();
    l293_init(&l293_channel);

    // when
    l293_disable(&l293_channel);

    // then
    TEST_ASSERT_FALSE(tim3_mock_verify_channel4_running());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_initialize_gpio_channels);
    RUN_TEST(should_initialize_timer3);
    RUN_TEST(should_initialize_pwm_on_timer3_channel4);
    RUN_TEST(should_initialize_pwm_on_timer3_channel3);
    RUN_TEST(should_enable_timer3);
    RUN_TEST(should_turn_right_the_right_channel);
    RUN_TEST(should_turn_right_the_left_channel);
    RUN_TEST(should_turn_left_the_right_channel);
    RUN_TEST(should_turn_left_the_left_channel);
    RUN_TEST(should_stop_running_left_channel);
    RUN_TEST(should_stop_running_right_channel);
    RUN_TEST(should_stop_left_channel);
    RUN_TEST(should_stop_right_channel);
    RUN_TEST(should_enable_pwm_signal);
    RUN_TEST(should_disable_pwm_signal);
    return UNITY_END();
}