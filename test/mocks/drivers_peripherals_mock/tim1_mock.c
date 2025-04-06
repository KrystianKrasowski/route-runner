#include "tim1_mock.h"
#include <tim1.h>

typedef struct tim1_mock
{
    int     init_calls;
    int     set_toggles_calls;
    uint8_t toggles;
} tim1_mock_t;

static tim1_mock_t mock;

void
tim1_ch1_init(void)
{
    mock.init_calls++;
}

void
tim1_ch1_set_toggles(uint8_t count)
{
    mock.toggles = count;
}

void
tim1_ch1_mock_reset(void)
{
    mock.init_calls        = 0;
    mock.set_toggles_calls = 0;
    mock.toggles           = 0;
}

int
tim1_ch1_mock_verify_init_calls(void)
{
    return mock.init_calls;
}

int
tim1_ch1_mock_verify_set_toggles_calls(void)
{
    return mock.set_toggles_calls;
}

uint8_t
tim1_ch1_mock_get_applied_toggles(void)
{
    return mock.toggles;
}