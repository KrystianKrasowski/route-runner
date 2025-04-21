/**
 * @brief Linebot route coordinates API
 *
 */

#ifndef _LINEBOT_COORDS_H
#define _LINEBOT_COORDS_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Coordinates object handle
 *
 */
typedef uint8_t linebot_coords_t;

/**
 * @brief Produces a handle to the linebot route coordinates object.
 *
 * Coordinates are based on values that represents the route detection
 * intensivity.
 *
 * @param[in] coordinates coordinates "visibility" values array; higher - more
 * visible
 * @param[in] weights coordinates "importance" values array; the higher the
 * absolute value, the greater the deviation from the center; negative values
 * are deviation to left side, positive - to the right
 * @param[in] size coordinates array size
 * @param[out] ph_self pointer to a handle of a coords object
 *
 * @retval 0 OK
 * @retval -12 ENOMEM
 */
int
linebot_coords_acquire(uint8_t const            coordinates[],
                       uint8_t const            size,
                       linebot_coords_t * const ph_self);

/**
 * @brief Release coords instance
 *
 * @param[in] h_self handle to a coords instance
 */
void
linebot_coords_release(linebot_coords_t const h_self);

#endif