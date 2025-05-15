#ifndef _PATHBOT_APPLICATION_MOCK_MOTION_H
#define _PATHBOT_APPLICATION_MOCK_MOTION_H

#include <pathbot/domain.h>

void
pathbot_port_mock_motion_reset(void);

int
pathbot_port_mock_motion_verify_apply_calls(void);

pathbot_motion_t
pathbot_port_mock_motion_get_applied(void);

#endif
