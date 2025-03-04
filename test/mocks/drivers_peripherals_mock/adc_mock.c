#include "adc_mock.h"
#include <string.h>

typedef struct
{
    int init_calls;
    int on_calls;
    int start_calls;
} adc_mock_t;

static adc_mock_t mock_state = {
    .init_calls  = 0,
    .on_calls    = 0,
    .start_calls = 0,
};

void
adc_init()
{
    mock_state.init_calls++;
}

void
adc_on(void)
{
    mock_state.on_calls++;
}

void
adc_start(void)
{
    mock_state.start_calls++;
}

int
adc_mock_verify_init_calls(void)
{
    return mock_state.init_calls;
}

int
adc_mock_verify_on_calls(void)
{
    return mock_state.on_calls;
}

int
adc_mock_verity_start_calls(void)
{
    return mock_state.start_calls;
}

void
adc_mock_reset(void)
{
    memset(&mock_state, 0, sizeof(mock_state));
}