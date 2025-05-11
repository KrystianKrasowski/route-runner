#include "commands.h"
#include "coords.h"
#include "mode.h"
#include <stddef.h>

static inline bool
is_tracking(pathbot_mode_t const mode);

static inline bool
is_detected(pathbot_mode_t const mode);

static inline bool
is_manual(pathbot_mode_t const mode);

static inline bool
is_following(pathbot_mode_t const mode);

static inline bool
is_recovering(pathbot_mode_t const mode);

pathbot_mode_t
mode_update_manual(pathbot_mode_t const current_mode, uint16_t const commands)
{
    pathbot_mode_t mode = current_mode;

    if (is_tracking(current_mode) && commands_has_break(commands))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (is_detected(current_mode) && commands_has_follow(commands))
    {
        mode = PATHBOT_MODE_FOLLOWING;
    }

    return mode;
}

pathbot_mode_t
mode_update_tracking(pathbot_mode_t const     current_mode,
                     pathbot_coords_t * const p_coords)
{
    pathbot_mode_t mode = current_mode;

    if (is_manual(current_mode) && coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_DETECTED;
    }
    else if (is_detected(current_mode) && !coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (is_following(current_mode) && !coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_RECOVERING;
    }
    else if (is_tracking(current_mode) && coords_is_on_finish(p_coords))
    {
        mode = PATHBOT_MODE_MANUAL;
    }
    else if (is_recovering(current_mode) && coords_is_on_route(p_coords))
    {
        mode = PATHBOT_MODE_FOLLOWING;
    }

    return mode;
}

static inline bool
is_tracking(pathbot_mode_t mode)
{
    return PATHBOT_MODE_FOLLOWING == mode || PATHBOT_MODE_RECOVERING == mode;
}

static inline bool
is_detected(pathbot_mode_t mode)
{
    return PATHBOT_MODE_DETECTED == mode;
}

static inline bool
is_manual(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_MANUAL == mode;
}

static inline bool
is_following(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_FOLLOWING == mode;
}

static inline bool
is_recovering(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_RECOVERING == mode;
}
