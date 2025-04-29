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

void
linebot_motion_init(void);

/**
 * @brief Produces a handle to the motion object.
 *
 * The steering value determines linebot turns. It allowes values from the
 * <-100,100> range. Edge values means the hardest turns.
 *
 * @param[in] direction direction in which linebot moves
 * @param[in] correction steering value
 * @param[out] ph_self handle of motion object
 *
 * @retval 0 OK
 * @retval -12 ENOMEM
 */
int
linebot_motion_acquire(linebot_direction_t const    direction,
                       int8_t const                 correction,
                       linebot_lgc_motion_t * const ph_self);

/**
 * @brief Release motion instance
 *
 * @param[in] h_self handle to a motion instance
 */
void
linebot_motion_release(linebot_lgc_motion_t h_self);

/**
 * @brief Returns motion direction
 *
 * @param[in] h_self handle to a motion instance
 *
 * @return linebot_motion_direction_t
 */
linebot_direction_t
linebot_motion_get_direction(linebot_lgc_motion_t const h_self);

/**
 * @brief Returns motion correction
 *
 * @param[in] h_self handle to a motion instance
 *
 * @return int8_t steering value
 */
int8_t
linebot_motion_get_correction(linebot_lgc_motion_t const h_self);

#endif
