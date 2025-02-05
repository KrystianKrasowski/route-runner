#include "tim3_mock.h"
#include <tim3.h>

static int tim3_ch1_init_calls = 0;

void
tim3_ch1_init(void)
{
    tim3_ch1_init_calls++;
}

int
tim3_ch1_mock_verify_init_calls(void)
{
    return tim3_ch1_init_calls;
}

void
tim3_ch1_mock_reset(void)
{
    tim3_ch1_init_calls = 0;
}