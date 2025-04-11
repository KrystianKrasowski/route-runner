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
 * Need to be called before anything else, due to ports and object pools
 * initializations.
 *
 */
void
linebot_init(void);

/**
 * @brief Produces a handle to a Linebot context object.
 *
 * @param mode starting mode
 * @param coords starting coords
 * @param errors_size size of the measured route drift errors
 * @param handle pointer to the handle of linebot instance
 * @return true linebot object successfully instantiated
 * @return false linebot object instantiation failed
 */
bool
linebot_new(linebot_mode_t    mode,
            linebot_coords_t  coords,
            uint8_t           errors_size,
            linebot_t * const handle);

/**
 * @brief Release linebot instance
 *
 * @param linebot handle to a linebot instance
 */
void
linebot_free(linebot_t linebot);

/**
 * @brief Returns current Linebot mode.
 *
 * @param self handle to a linebot instance
 * @return linebot_mode_t
 */
linebot_mode_t
linebot_get_mode(linebot_t const self);

/**
 * @brief Apply new motion to the given commands.
 *
 * Note that the manual motion application is limited to the certain linebot
 * modes. If the vehicle is in tracking mode the manual motion will not be
 * applied, unless the break command occurs.
 *
 * @param self handle to a linebot instance
 * @param commands The commands given by external control
 * @return linebot_result_t
 */
linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands);

/**
 * @brief Change mode to the given commands.
 *
 * Possible mode transitions are:
 * * `detected` -> `following` (a subset of `tracking`)
 * * `tracking` -> `manual`
 *
 * @param self handle to a linebot instance
 * @param commands The commands given by external control
 * @return linebot_result_t
 */
linebot_result_t
linebot_change_mode_by_control(linebot_t const self, uint16_t const commands);

/**
 * @brief Apply new motion to the given route coordinates.
 *
 * Note that the tracking motion is applied only for tracking mode, unless
 * linebot meets the finish position.
 *
 * @param self handle to a linebot instance
 * @param coords The route coordinates by external source
 * @return linebot_result_t
 */
linebot_result_t
linebot_apply_tracking_motion(linebot_t const        self,
                              linebot_coords_t const coords);

/**
 * @brief Change mode to the given route coordinates.
 *
 * Possible mode transitions are:
 * * `manual` -> `detected`
 * * `detected` -> `manual`
 * * `tracking` -> `manual`
 * * `following` -> `recovering`
 * * `recovering` -> `following`
 *
 * @param self handle to a linebot instance
 * @param coords The route coordinates by external source
 * @return linebot_result_t
 */
linebot_result_t
linebot_change_mode_by_coords(linebot_t const        self,
                              linebot_coords_t const coords);

/**
 * @brief Stops linebot immediately.
 *
 * @param self handle to a linebot instance
 * @return linebot_result_t
 */
linebot_result_t
linebot_stop(linebot_t const self);

#endif