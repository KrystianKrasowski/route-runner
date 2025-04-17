#ifndef _ADAPTERS_H
#define _ADAPTERS_H

#include <linebot/coords.h>
#include <stdint.h>

void
adapters_control_init(void);

uint16_t
adapters_control_parse(uint8_t const *p_byte_buffer);

void
adapters_coords_init(void);

int
adapters_coords_parse(uint8_t const *p_byte_buffer, linebot_coords_t *coords);

int
adapters_coords_map(uint8_t const *raw, linebot_coords_t *coords);

void
adapters_mode_init(void);

void
adapters_motion_init(void);

#endif