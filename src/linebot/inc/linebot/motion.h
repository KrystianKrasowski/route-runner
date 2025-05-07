/**
 * @brief Linebot motion API
 *
 */

#ifndef _LINEBOT_MOTION_H
#define _LINEBOT_MOTION_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Available motion directions.
 *
 */
typedef enum
{
    LINEBOT_DIRECTION_NONE,
    LINEBOT_DIRECTION_FORWARD,
    LINEBOT_DIRECTION_BACKWARD,
} linebot_direction_t;

/**
 * @brief Motion object handle
 *
 */
typedef uint8_t linebot_lgc_motion_t;

typedef struct
{
    linebot_direction_t const direction;
    int8_t const              correction;
} linebot_motion_t;

linebot_direction_t
linebot_motion_invert_direction(linebot_motion_t const *p_self);

#endif
