#ifndef _PATHBOT_MOTION_H
#define _PATHBOT_MOTION_H

#include <pathbot/domain.h>

bool
motion_update_manual(uint16_t const           commands,
                     pathbot_motion_t * const p_motion);

bool
motion_update_pid(int8_t const                     error,
                  stack_t const * const            p_past_errors,
                  pathbot_pid_conf_t const * const p_pid,
                  pathbot_motion_t * const         p_motion);

void
motion_stop(pathbot_motion_t * const p_motion);

bool
motion_equals(pathbot_motion_t const * const p_self,
              pathbot_motion_t const * const p_other);

#endif
