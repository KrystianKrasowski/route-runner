#ifndef _TIM15_MOCK_H
#define _TIM15_MOCK_H

void
tim15_mock_reset(void);

int
tim15_mock_verify_init_calls(void);

int
tim15_mock_verify_start_calls(void);

int
tim15_mock_verify_reset_calls(void);

int
tim15_mock_verify_stop_calls(void);

#endif