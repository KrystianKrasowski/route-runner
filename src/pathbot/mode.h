#ifndef _PATHBOT_MODE_H
#define _PATHBOT_MODE_H

#include <pathbot.h>
#include <stdbit.h>

bool
mode_is_tracking(pathbot_mode_t const mode);

bool
mode_is_detected(pathbot_mode_t const mode);

bool
mode_is_manual(pathbot_mode_t const mode);

bool
mode_is_following(pathbot_mode_t const mode);

bool
mode_is_recovering(pathbot_mode_t const mode);

#endif
