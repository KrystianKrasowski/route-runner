#ifndef _SYSCLOCK_H
#define _SYSCLOCK_H

#include <stdint.h>

#define SYSCLOCK_FREQ 16000000UL
#define APB1_CLK      SYSCLOCK_FREQ

void
sysclock_init(void);

uint32_t
sysclock_get_prescaller_base(uint32_t resolution);

#endif