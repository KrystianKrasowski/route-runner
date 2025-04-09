#ifndef _LINEBOT_MOTION_H
#define _LINEBOT_MOTION_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    LINEBOT_MOTION_NONE,
    LINEBOT_MOTION_FORWARD,
    LINEBOT_MOTION_BACKWARD,
} linebot_motion_direction_t;

typedef uint8_t linebot_motion_t;

bool
linebot_motion_new(linebot_motion_direction_t const direction,
                   int8_t                           correction,
                   linebot_motion_t * const         handle);

void
linebot_motion_free(linebot_motion_t motion);

linebot_motion_direction_t
linebot_motion_get_direction(linebot_motion_t const self);

int8_t
linebot_motion_get_correction(linebot_motion_t const self);

#endif