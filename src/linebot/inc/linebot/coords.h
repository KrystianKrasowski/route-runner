/**
 * @brief Linebot route coordinates API
 *
 */

#ifndef _LINEBOT_COORDS_H
#define _LINEBOT_COORDS_H

#include "result.h"
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
 * Coordinates are based on 6 values that represents the route detection
 * intensivity.
 *
 * @param[in] l3 furthest from center detection on the left side of the route
 * @param[in] l2 middle detection on the left side of the route
 * @param[in] l1 nearset to center detection on the left side of the route
 * @param[in] r1 nearset to center detection on the right side of the route
 * @param[in] r2 middle detection on the right side of the route
 * @param[in] r3 furthest from center detection on the right side of the route
 * @param[out] handle handle of coords object
 *
 * @retval LINEBOT_OK
 * @retval LINEBOT_ERR_POOL_EXCEEDED
 */
linebot_result_t
linebot_coords_acquire(uint8_t const            l3,
                       uint8_t const            l2,
                       uint8_t const            l1,
                       uint8_t const            r1,
                       uint8_t const            r2,
                       uint8_t const            r3,
                       linebot_coords_t * const handle);

/**
 * @brief Release coords instance
 *
 * @param[in] coords handle to a coords instance
 */
void
linebot_coords_release(linebot_coords_t const coords);

#endif