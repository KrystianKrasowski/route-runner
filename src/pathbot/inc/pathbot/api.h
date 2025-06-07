#ifndef _PATHBOT_API_H
#define _PATHBOT_API_H

#include <pathbot/domain.h>
#include <stdint.h>

bool
pathbot_mode_is_recovering(pathbot_mode_t const mode);

bool
pathbot_mode_is_tracking(pathbot_mode_t const mode);

void
pathbot_mode_get_name(pathbot_mode_t const mode, char *name);

pathbot_direction_t
pathbot_motion_invert_direction(pathbot_motion_t const * const p_motion);

void
pathbot_handle_commands(uint16_t const commands);

void
pathbot_handle_coords(pathbot_coords_t const * const p_coords);

void
pathbot_handle_route_guard_timeout(void);

void
pathbot_handle_store_dump(void);

#endif
