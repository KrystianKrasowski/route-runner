#ifndef _ADAPTERS_H
#define _ADAPTERS_H

#include <linebot/coords.h>
#include <stdint.h>

void
adapters_control_init(void);

int
adapters_control_read(uint16_t *p_commands);

void
adapters_coords_init(void);

int
adapters_coords_create_default(linebot_coords_t *ph_coords);

int
adapters_coords_read(linebot_coords_t *ph_coords);

void
adapters_mode_init(void);

bool
adapters_is_route_guard_timeout(void);

void
adapters_motion_init(void);

#endif