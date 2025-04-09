#ifndef _LINEBOT_MODE_H
#define _LINEBOT_MODE_H

#include <stdbool.h>

typedef enum
{
    LINEBOT_MODE_MANUAL,
    LINEBOT_MODE_DETECTED,
    LINEBOT_MODE_FOLLOWING,
    LINEBOT_MODE_RECOVERING,
} linebot_mode_t;

bool
linebot_mode_is_manual(linebot_mode_t const self);

bool
linebot_mode_is_detected(linebot_mode_t const self);

bool
linebot_mode_is_tracking(linebot_mode_t const self);

bool
linebot_mode_is_following(linebot_mode_t const self);

bool
linebot_mode_is_recovering(linebot_mode_t const self);

#endif