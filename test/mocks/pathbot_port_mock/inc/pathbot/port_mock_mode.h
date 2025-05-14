#ifndef _PATHBOT_APPLICATION_MOCK_MOTION_H
#define _PATHBOT_APPLICATION_MOCK_MOTION_H

#include <pathbot/domain.h>
#include <pathbot/port.h>

int
pathbot_port_mock_mode_verify_changed_calls(void);

pathbot_mode_t
pathbot_port_mock_mode_get_changed_mode(void);

#endif
