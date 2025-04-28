#ifndef _DEVICES_MOCK_L293_H
#define _DEVICES_MOCK_L293_H

#include <devices/l293.h>
#include <stdbool.h>

typedef enum
{
    L293_MOCK_STATE_LEFT,
    L293_MOCK_STATE_RIGHT,
    L293_MOCK_STATE_STOP,
} l293_mock_state_t;

void
devices_l293_mock_init(void);

void
devices_l293_mock_deinit(void);

l293_mock_state_t
devices_l293_mock_get_state(l293_t const h_self);

bool
devices_l293_mock_is_enabled(l293_t const h_self);

uint8_t
devices_l293_mock_get_ducy_cycle(l293_t const h_self);

#endif
