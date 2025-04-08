#ifndef _LINEBOT_PORTS_MOCK_MODE_H
#define _LINEBOT_PORTS_MOCK_MODE_H

#include <linebot.h>

void
linebot_port_mock_mode_init(void);

int
linebot_port_mock_mode_verify_changed_calls(void);

linebot_mode_t
linebot_port_mock_mode_get_changed_mode(void);

#endif