#ifndef _PATHBOT_MODE_H
#define _PATHBOT_MODE_H

#include <pathbot/domain.h>

bool
mode_is_tracking(pathbot_mode_t const mode);

bool
mode_update_manual(uint16_t const commands, pathbot_mode_t * const p_mode);

bool
mode_update_tracking(pathbot_coords_t const * const p_coords,
                     pathbot_mode_t * const         p_mode);

#endif
