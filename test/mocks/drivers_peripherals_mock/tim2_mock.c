#include "tim2_mock.h"
#include <tim2.h>

static int tim2_ch1_init_calls = 0;

void
tim2_ch1_init(void)
{
    tim2_ch1_init_calls++;
}

int
tim2_ch1_mock_verify_init_calls(void)
{
    return tim2_ch1_init_calls;
}

void
tim2_ch1_mock_reset(void)
{
    tim2_ch1_init_calls = 0;
}