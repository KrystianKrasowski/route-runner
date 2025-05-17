#ifndef _PATHBOT_API_H
#define _PATHBOT_API_H

#include <pathbot/domain.h>
#include <stdint.h>

// TODO: Remove this in favour of utils result
typedef enum
{
    PATHBOT_RESULT_OK = 0,
    PATHBOT_RESULT_NOOP,
} pathbot_result_t;

bool
pathbot_mode_is_recovering(pathbot_mode_t const mode);

bool
pathbot_mode_is_tracking(pathbot_mode_t const mode);

pathbot_direction_t
pathbot_motion_invert_direction(pathbot_motion_t const * const p_motion);

int
pathbot_handle_commands(uint16_t const commands);

int
pathbot_handle_coords(pathbot_coords_t const * const p_coords);

int
pathbot_handle_route_guard_timeout(void);

#endif
