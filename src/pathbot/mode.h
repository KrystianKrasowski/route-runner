#ifndef _PATHBOT_MODE_H
#define _PATHBOT_MODE_H

#include <pathbot.h>
#include <stdbit.h>

pathbot_mode_t
mode_update_manual(pathbot_mode_t const current_mode, uint16_t const commands);

pathbot_mode_t
mode_update_tracking(pathbot_mode_t const           current_mode,
                     pathbot_coords_t const * const p_coords);

#endif
