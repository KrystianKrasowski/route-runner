#ifndef _DEVICES_TIMEOUT_GUARD_MOCK_H
#define _DEVICES_TIMEOUT_GUARD_MOCK_H

#include <devices/timeout_guard.h>
#include <stdbool.h>

void
device_timeout_guard_mock_init(void);

void
device_timeout_guard_mock_deinit(void);

bool
device_timeout_guard_mock_is_started(device_timeout_guard_t const h_self);

bool
device_timeout_guard_mock_is_stopped(device_timeout_guard_t const h_self);

void
device_timeout_guard_mock_set_ready(device_timeout_guard_t const h_self,
                                    bool const                   ready);

#endif
