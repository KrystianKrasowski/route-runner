/**
 * @brief Linebot SPI (service provider interface)
 *
 * Serves as the inbound ports from hexagonal application architecture
 *
 */

#ifndef _LINEBOT_SPI_H
#define _LINEBOT_SPI_H

#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <stdint.h>

typedef uint8_t linebot_port_motion_t;
typedef uint8_t linebot_port_mode_t;

/**
 * @brief Applies motion to the external motion handler
 *
 * Can serve as DC motor driver
 *
 * @deprecated
 * @param[in] h_self handle to port instance
 * @param[in] h_motion handle to linebot motion
 */
void
linebot_lgc_port_motion_apply(linebot_lgc_motion_t const h_motion);

/**
 * @brief Applies motion to the external motion handler
 *
 * Can serve as DC motor driver
 *
 * @param[in] h_self handle to port instance
 * @param[in] h_motion handle to linebot motion
 */
int
linebot_port_motion_apply(linebot_port_motion_t const h_self,
                          linebot_motion_t const     *p_motion);

/**
 * @brief Triggers an event on linebot motion change to be handled by
 * infrastructure
 *
 * @param[in] h_self handle to port instance
 * @param[in] value linebot current mode
 */
void
linebot_port_mode_changed(linebot_mode_t const value);

#endif
