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
    LINEBOT_MOTION_NONE,
    LINEBOT_MOTION_FORWARD,
    LINEBOT_MOTION_BACKWARD,
} linebot_motion_direction_t;

/**
 * @brief Motion object handle
 *
 */
typedef uint8_t linebot_motion_t;

/**
 * @brief Produces a handle to the motion object.
 *
 * The steering value determines linebot turns. It allowes values from the
 * <-100,100> range. Edge values means the hardest turns.
 *
 * @param direction direction in which linebot moves
 * @param correction steering value
 * @param handle pointed to the handle of motion object
 * @return true motion object successfully instantiated
 * @return false motion object instantiation falied
 */
bool
linebot_motion_new(linebot_motion_direction_t const direction,
                   int8_t const                     correction,
                   linebot_motion_t * const         handle);

/**
 * @brief Release motion instance
 *
 * @param motion handle to a motion instance
 */
void
linebot_motion_free(linebot_motion_t motion);

/**
 * @brief Returns motion direction
 * 
 * @param self handle to a motion instance
 * @return linebot_motion_direction_t 
 */
linebot_motion_direction_t
linebot_motion_get_direction(linebot_motion_t const self);

/**
 * @brief Returns motion correction
 * 
 * @param self handle to a motion instance
 * @return int8_t steering value
 */
int8_t
linebot_motion_get_correction(linebot_motion_t const self);

#endif