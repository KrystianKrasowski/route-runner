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
 * @param[in] direction direction in which linebot moves
 * @param[in] correction steering value
 * @param[out] handle handle of motion object
 * 
 * @retval 0 OK
 * @retval -12 ENOMEM
 */
int
linebot_motion_acquire(linebot_motion_direction_t const direction,
                       int8_t const                     correction,
                       linebot_motion_t * const         handle);

/**
 * @brief Release motion instance
 *
 * @param[in] motion handle to a motion instance
 */
void
linebot_motion_release(linebot_motion_t motion);

/**
 * @brief Returns motion direction
 *
 * @param[in] self handle to a motion instance
 * 
 * @return linebot_motion_direction_t
 */
linebot_motion_direction_t
linebot_motion_get_direction(linebot_motion_t const self);

/**
 * @brief Returns motion correction
 *
 * @param[in] self handle to a motion instance
 * 
 * @return int8_t steering value
 */
int8_t
linebot_motion_get_correction(linebot_motion_t const self);

#endif