#include "tim15_mock.h"
#include <tim15.h>

typedef struct tim15_mock
{
    int init_calls;
    int start_calls;
    int reset_calls;
    int stop_calls;
} tim15_mock_t;

static tim15_mock_t mock;

void
tim15_init(void)
{
    mock.init_calls++;
}

void
tim15_start(void)
{
    mock.start_calls++;
}

void
tim15_reset(void)
{
    mock.reset_calls++;
}

void
tim15_stop(void)
{
    mock.stop_calls++;
}

void
tim15_mock_reset(void)
{
    mock.init_calls  = 0;
    mock.start_calls = 0;
    mock.reset_calls = 0;
    mock.stop_calls  = 0;
}

int
tim15_mock_verify_init_calls(void)
{
    return mock.init_calls;
}

int
tim15_mock_verify_start_calls(void)
{
    return mock.start_calls;
}

int
tim15_mock_verify_reset_calls(void)
{
    return mock.reset_calls;
}

int
tim15_mock_verify_stop_calls(void)
{
    return mock.stop_calls;
}