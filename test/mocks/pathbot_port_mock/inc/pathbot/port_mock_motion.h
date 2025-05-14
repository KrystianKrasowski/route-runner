#ifndef _PATHBOT_APPLICATION_MOCK_MOTION_H
#define _PATHBOT_APPLICATION_MOCK_MOTION_H

#include <pathbot/domain.h>

int
pathbot_port_mock_motion_verify_apply_calls(void);

pathbot_motion_t
pathbot_port_mock_motion_get_applied_motion(void);

#endif
