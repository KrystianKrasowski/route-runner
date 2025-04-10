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
 * @brief Initializes external control
 *
 * Can be used for drivers initialization, etc.
 *
 */
void
linebot_port_control_init(void);

/**
 * @brief Translates external command to the linebot domain.
 *
 * @param raw_command external commands
 * @return uint16_t domain commands
 */
uint16_t
linebot_port_control_command_map(uint16_t const raw_command);

/**
 * @brief Initializes external coordinations handler
 *
 * Can be used for drivers initialization, etc.
 *
 */
void
linebot_port_coords_init(void);

/**
 * @brief Translates external coodinates to the linebot domain.
 *
 * @param raw external coordinates array
 * @return linebot_coords_t domain coordinates
 */
linebot_coords_t
linebot_port_coords_map(uint8_t const *raw);

/**
 * @brief Initializes external motion handler
 *
 * Can be used for drivers initialization, etc
 *
 */
void
linebot_port_motion_init(void);

/**
 * @brief Applies motion to the external motion handler
 *
 * Can serve as DC motor driver
 *
 * @param motion linebot motion
 */
void
linebot_port_motion_apply(linebot_motion_t const motion);

/**
 * @brief Initializes external mode handler
 *
 * Can be used for drivers initialization, etc.
 *
 */
void
linebot_port_mode_init(void);

/**
 * @brief Triggers an event on linebot motion change to be handled by
 * infrastructure
 *
 * @param value linebot current mode
 */
void
linebot_port_mode_changed(linebot_mode_t const value);

#endif