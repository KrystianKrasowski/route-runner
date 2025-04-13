/**
 * @brief Linebot mode API.
 * 
 */

#ifndef _LINEBOT_MODE_H
#define _LINEBOT_MODE_H

#include <stdbool.h>

/**
 * @brief Available linebot mode values.
 * 
 */
typedef enum
{
    LINEBOT_MODE_MANUAL,
    LINEBOT_MODE_DETECTED,
    LINEBOT_MODE_FOLLOWING,
    LINEBOT_MODE_RECOVERING,
} linebot_mode_t;

/**
 * @brief Verifies manual mode.
 * 
 * @param[in] self mode value
 * 
 * @retval true 
 * @retval false 
 */
bool
linebot_mode_is_manual(linebot_mode_t const self);

/**
 * @brief Verifies route detected mode.
 * 
 * @param[in] self mode value
 * 
 * @retval true 
 * @retval false 
 */
bool
linebot_mode_is_detected(linebot_mode_t const self);

/**
 * @brief Verifies tracking mode.
 * 
 * Both `following` and `recovering` are considered `tracking`.
 * 
 * @param[in] self mode value
 * 
 * @retval true 
 * @retval false 
 */
bool
linebot_mode_is_tracking(linebot_mode_t const self);

/**
 * @brief Verifies following mode.
 * 
 * @param[in] self mode value
 * 
 * @retval true 
 * @retval false 
 */
bool
linebot_mode_is_following(linebot_mode_t const self);

/**
 * @brief Verifies recovering mode.
 * 
 * @param[in][in] self mode value
 * 
 * @retval true 
 * @retval false 
 */
bool
linebot_mode_is_recovering(linebot_mode_t const self);

#endif