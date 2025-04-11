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
 * @param l3 furthest from center detection on the left side of the route
 * @param l2 middle detection on the left side of the route
 * @param l1 nearset to center detection on the left side of the route
 * @param r1 nearset to center detection on the right side of the route
 * @param r2 middle detection on the right side of the route
 * @param r3 furthest from center detection on the right side of the route
 * @param handle pointer to the handle of coords object
 *
 * @return LINEBOT_OK coords object successfully instantiated
 * @return LINEBOT_ERR_POOL_EXCEEDED coords object instantiation failed
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
 * @param coords handle to a coords instance
 */
void
linebot_coords_release(linebot_coords_t const coords);

#endif