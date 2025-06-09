#ifndef _PATHBOT_APPLICATION_PORT_H
#define _PATHBOT_APPLICATION_PORT_H

#include <pathbot/domain.h>

void
pathbot_port_mode_changed(pathbot_mode_t const mode);

void
pathbot_port_motion_apply(pathbot_motion_t const * const motion);

void
pathbot_port_dump_mode(pathbot_mode_t const mode);

void
pathbot_port_dump_pid_conf(pathbot_pid_conf_t const *p_pid_conf);

#endif
