#ifndef _PATHBOT_PORT_MOCK_DUMP_H
#define _PATHBOT_PORT_MOCK_DUMP_H

#include <pathbot/domain.h>

void
pathbot_port_mock_dump_reset(void);

pathbot_mode_t
pathbot_port_mock_dump_verify_mode(void);

float
pathbot_port_mock_dump_verify_pid_kp(void);

float
pathbot_port_mock_dump_verify_pid_ki(void);

float
pathbot_port_mock_dump_verify_pid_kd(void);

#endif
