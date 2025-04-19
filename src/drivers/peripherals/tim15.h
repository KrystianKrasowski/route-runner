#ifndef _TIM15_H
#define _TIM15_H

#include <stdbool.h>

void
tim15_init(void);

void
tim15_start(void);

void
tim15_stop(void);

bool
tim15_is_timeout(void);

#endif