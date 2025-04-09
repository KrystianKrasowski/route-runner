#ifndef _LINEBOT_SPI_H
#define _LINEBOT_SPI_H

#include "coords.h"
#include "mode.h"
#include "motion.h"

void
linebot_port_control_init(void);

uint16_t
linebot_port_control_command_map(uint16_t const raw_command);

void
linebot_port_coords_init(void);

linebot_coords_t
linebot_port_coords_map(uint8_t *raw);

void
linebot_port_motion_init(void);

void
linebot_port_motion_apply(linebot_motion_t const motion);

void
linebot_port_mode_init(void);

void
linebot_port_mode_changed(linebot_mode_t const value);

#endif