#ifndef _LINEBOT_PORTS_MOCK_MOTION_H
#define _LINEBOT_PORTS_MOCK_MOTION_H

#include <linebot.h>

void
linebot_port_mock_motion_init(void);

bool
linebot_port_mock_motion_verify_applied(void);

linebot_motion_t
linebot_port_mock_motion_get_applied(void);

int
linebot_port_mock_motion_verify_apply_calls(void);

#endif