#ifndef _LINEBOT_PORTS_MOCK_MOTION_H
#define _LINEBOT_PORTS_MOCK_MOTION_H

#include <linebot/motion.h>

void
linebot_port_mock_motion_init(void);

bool
linebot_port_mock_motion_verify_applied(void);

linebot_direction_t
linebot_port_mock_motion_get_direction(void);

int8_t
linebot_port_mock_motion_get_correction(void);

int
linebot_port_mock_motion_verify_apply_calls(void);

#endif
