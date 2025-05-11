#ifndef _PATHBOT_MOTION_H
#define _PATHBOT_MOTION_H

#include <pathbot.h>

pathbot_motion_t
motion_create_manual(uint16_t const commands);

pathbot_motion_t
motion_create_pid(int8_t const                     error,
                  stack_t const * const            p_past_errors,
                  pathbot_pid_conf_t const * const p_pid_conf);

#endif
