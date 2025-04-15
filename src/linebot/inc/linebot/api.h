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
#include "result.h"

/**
 * @brief Linebot API context object handle.
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
 * @param[in] coords starting coords
 * @param[in] errors_size size of the measured route drift errors collection
 * @param[out] handle handle of linebot instance
 *
 * @retval LINEBOT_OK linebot object successfully instantiated
 * @retval LINEBOT_ERR_POOL_EXCEEDED linebot object instantiation failed
 */
linebot_result_t
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errors_size,
                linebot_t * const handle);

/**
 * @brief Produces a handle to a Linebot context object with default values.
 *
 * @param[out] handle handle of linebot instance
 *
 * @retval LINEBOT_OK linebot object successfully instantiated
 * @retval LINEBOT_ERR_POOL_EXCEEDED linebot object instantiation failed
 */
linebot_result_t
linebot_acquire_default(linebot_t * const handle);

/**
 * @brief Release linebot instance
 *
 * @param[in] linebot handle to a linebot instance
 */
void
linebot_release(linebot_t const linebot);

/**
 * @brief Returns current Linebot mode.
 *
 * @param[in] self handle to a linebot instance
 * @param[out] mode mode value
 *
 * @retval LINEBOT_OK
 * @retval LINEBOT_ERR_NULL_POINTER
 */
linebot_result_t
linebot_get_mode(linebot_t const self, linebot_mode_t * const mode);

/**
 * @brief Apply new motion for the given commands.
 *
 * Note that the manual motion application is limited to the certain linebot
 * modes. If the vehicle is in tracking mode the manual motion will not be
 * applied, unless the break command occurs.
 *
 * @param[in] self handle to a linebot instance
 * @param[in] commands commands given by external control
 *
 * @retval LINEBOT_OK
 * @retval LINEBOT_ERR_NULL_POINTER
 */
linebot_result_t
linebot_handle_manual_control(linebot_t const self, uint16_t const commands);

/**
 * @brief Apply new motion for the given route coordinates.
 *
 * Note that the tracking motion is applied only for tracking mode, unless
 * linebot meets the finish position.
 *
 * @param[in] self handle to a linebot instance
 * @param[in] coords The route coordinates by external source
 *
 * @retval LINEBOT_OK
 * @retval LINEBOT_ERR_NULL_POINTER
 */
linebot_result_t
linebot_handle_route_tracking(linebot_t const        self,
                              linebot_coords_t const coords);

/**
 * @brief Stops linebot immediately.
 *
 * @param[in] self handle to a linebot instance
 *
 * @retval LINEBOT_OK
 * @retval LINEBOT_ERR_NULL_POINTER
 */
linebot_result_t
linebot_stop(linebot_t const self);

#endif