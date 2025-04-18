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

/**
 * @brief Applies motion to the external motion handler
 *
 * Can serve as DC motor driver
 *
 * @param[in] h_motion handle to linebot motion
 */
void
linebot_port_motion_apply(linebot_motion_t const h_motion);

/**
 * @brief Triggers an event on linebot motion change to be handled by
 * infrastructure
 *
 * @param[in] value linebot current mode
 */
void
linebot_port_mode_changed(linebot_mode_t const value);

#endif