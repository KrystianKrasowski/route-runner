#include "tim3_mock.h"
#include <tim3.h>

struct tim3_mock
{
    int  tim3_init_calls;
    int  tim3_ch4_pwm_init_calls;
    int  tim3_ch3_pwm_init_calls;
    bool tim3_enabled;
    bool tim3_ch3_running;
    bool tim3_ch4_running;
};

static struct tim3_mock mock;

void
tim3_init(void)
{
    mock.tim3_init_calls++;
}

void
tim3_enable(void)
{
    mock.tim3_enabled = true;
}

void
tim3_channel_pwm_init(tim3_channel_t channel)
{
    if (channel == TIM3_CHANNEL_3)
    {
        mock.tim3_ch3_pwm_init_calls++;
    }

    if (channel == TIM3_CHANNEL_4)
    {
        mock.tim3_ch4_pwm_init_calls++;
    }
}

void
tim3_channel_pwm_run(tim3_channel_t channel)
{
    if (channel == TIM3_CHANNEL_3)
    {
        mock.tim3_ch3_running = true;
    }

    if (channel == TIM3_CHANNEL_4)
    {
        mock.tim3_ch4_running = true;
    }
}

void
tim3_channel_pwm_stop(tim3_channel_t channel)
{
    if (channel == TIM3_CHANNEL_3)
    {
        mock.tim3_ch3_running = false;
    }

    if (channel == TIM3_CHANNEL_4)
    {
        mock.tim3_ch4_running = false;
    }
}

int
tim3_mock_verify_init_calls(void)
{
    return mock.tim3_init_calls;
}

bool
tim3_mock_verify_enabled(void)
{
    return mock.tim3_enabled;
}

int
tim3_mock_verify_pwm_init_on_channel4(void)
{
    return mock.tim3_ch4_pwm_init_calls;
}

int
tim3_mock_verify_pwm_init_on_channel3(void)
{
    return mock.tim3_ch3_pwm_init_calls;
}

bool
tim3_mock_verify_channel3_running(void)
{
    return mock.tim3_ch3_running;
}

bool
tim3_mock_verify_channel4_running(void)
{
    return mock.tim3_ch4_running;
}

void
tim3_mock_reset(void)
{
    mock.tim3_init_calls         = 0;
    mock.tim3_ch4_pwm_init_calls = 0;
    mock.tim3_ch3_pwm_init_calls = 0;
    mock.tim3_enabled            = false;
    mock.tim3_ch3_running        = false;
    mock.tim3_ch4_running        = false;
}