#include <tim3.h>

int
main(void)
{
    tim3_pwm_t pwm_channel3 = {TIM3_CHANNEL_3, 90};
    tim3_pwm_t pwm_channel4 = {TIM3_CHANNEL_4, 90};

    tim3_init();
    tim3_pwm_init(&pwm_channel3);
    tim3_pwm_init(&pwm_channel4);
    tim3_enable();
    tim3_pwm_run(&pwm_channel3);
    tim3_pwm_run(&pwm_channel4);

    while (1)
    {
    }
}