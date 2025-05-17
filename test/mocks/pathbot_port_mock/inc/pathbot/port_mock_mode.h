#ifndef _PATHBOT_APPLICATION_MOCK_MODE_H
#define _PATHBOT_APPLICATION_MOCK_MODE_H

#include <pathbot/domain.h>
#include <pathbot/port.h>

void
pathbot_port_mock_mode_reset(void);

int
pathbot_port_mock_mode_verify_changed_calls(void);

pathbot_mode_t
pathbot_port_mock_mode_get_changed_mode(void);

#endif
