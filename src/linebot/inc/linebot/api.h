/**
 * @brief The public API for controlling line following robot.
 *
 */

#ifndef _LINEBOT_API_H
#define _LINEBOT_API_H

#include "command.h"
#include "coords.h"
#include "mode.h"
#include "motion.h"

/**
 * @brief Linebot API context object ph_self.
 *
 */
typedef uint8_t linebot_t;

/**
 * @brief Initializes Linebot library.
 *
 * Need to be called before any use case, due to object pools initialization.
 *
 */
void
linebot_init(void);

/**
 * @brief Produces a handle to a linebot context object.
 *
 * @param[in] mode starting mode
 * @param[in] h_coords starting h_coords
 * @param[in] errors_size size of the measured route drift errors collection
 * @param[out] ph_self handle of linebot instance
 *
 * @retval 0 OK linebot object successfully instantiated
 * @retval -12 ENOMEM linebot object instantiation failed due to pool exhaustion
 * @retval -22 EINVAL invalid input argument(s)
 */
int
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  h_coords,
                uint8_t           errors_size,
                linebot_t * const ph_self);

/**
 * @brief Produces a handle to a Linebot context object with default values.
 *
 * @param[out] ph_self handle of linebot instance
 *
 * @retval 0 OK linebot object successfully instantiated
 * @retval -12 ENOMEM linebot object instantiation failed due to pool exhaustion
 */
int
linebot_acquire_default(linebot_t * const ph_self);

/**
 * @brief Release linebot instance
 *
 * @param[in] ph_self handle to a linebot instance
 */
void
linebot_release(linebot_t const ph_self);

/**
 * @brief Returns current Linebot mode.
 *
 * @param[in] h_self handle to a linebot instance
 * @param[out] p_mode pointer to a mode value
 *
 * @retval 0 OK
 * @retval -22 EINVAL Invalid linebot handle
 */
int
linebot_get_mode(linebot_t const h_self, linebot_mode_t * const p_mode);

/**
 * @brief Apply new motion for the given commands.
 *
 * Note that the manual motion application is limited to the certain linebot
 * modes. If the vehicle is in tracking mode the manual motion will not be
 * applied, unless the break command occurs.
 *
 * @param[in] h_self handle to a linebot instance
 * @param[in] commands commands given by external control
 *
 * @retval 0 OK
 * @retval -22 EINVAL Invalid linebot handle
 */
int
linebot_handle_manual_control(linebot_t const h_self, uint16_t const commands);

/**
 * @brief Apply new motion for the given route coordinates.
 *
 * Note that the tracking motion is applied only for tracking mode, unless
 * linebot meets the finish position.
 *
 * @param[in] h_self handle to a linebot instance
 * @param[in] h_coords handle to a route coordinates by external source
 *
 * @retval 0 OK
 * @retval -22 EINVAL Invalid linebot handle
 */
int
linebot_handle_route_tracking(linebot_t const        h_self,
                              linebot_coords_t const h_coords);

/**
 * @brief Stops linebot immediately.
 *
 * @param[in] h_self handle to a linebot instance
 *
 * @retval 0 OK
 * @retval -22 EINVAL Invalid linebot handle
 */
int
linebot_handle_immediate_stop(linebot_t const h_self);

#endif