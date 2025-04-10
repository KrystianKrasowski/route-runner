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
 * Coordinates are based on 6 values that represents the route detection
 * intensivity.
 *
 * @param l3 The furthest from center detection on the left side of the route
 * @param l2 The middle detection on the left side of the route
 * @param l1 The nearset to center detection on the left side of the route
 * @param r1 The nearset to center detection on the right side of the route
 * @param r2 The middle detection on the right side of the route
 * @param r3 The furthest from center detection on the right side of the route
 * @param handle Pointer to the handle of coords object
 * @return true Coords object created successfully
 * @return false Coords object pool failure
 */
bool
linebot_new_coords(uint8_t const            l3,
                   uint8_t const            l2,
                   uint8_t const            l1,
                   uint8_t const            r1,
                   uint8_t const            r2,
                   uint8_t const            r3,
                   linebot_coords_t * const handle);

/**
 * @brief Return coords object to the pool
 *
 * @param coords Handle to a coords object
 */
void
linebot_free_coords(linebot_coords_t const coords);

#endif