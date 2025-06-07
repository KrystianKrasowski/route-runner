#include "commands.h"
#include "coords.h"
#include "mode.h"
#include <pathbot/api.h>
#include <stddef.h>
#include <string.h>

static inline bool
is_detected(pathbot_mode_t const mode);

static inline bool
is_manual(pathbot_mode_t const mode);

static inline bool
is_following(pathbot_mode_t const mode);

bool
pathbot_mode_is_recovering(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_RECOVERING == mode;
}

bool
pathbot_mode_is_tracking(pathbot_mode_t mode)
{
    return is_following(mode) || pathbot_mode_is_recovering(mode);
}

void
pathbot_mode_get_name(pathbot_mode_t const mode, char *name)
{
    switch (mode)
    {
        case PATHBOT_MODE_DETECTED:
            strcpy(name, "detected");
            break;

        case PATHBOT_MODE_RECOVERING:
            strcpy(name, "recovering");
            break;

        case PATHBOT_MODE_FOLLOWING:
            strcpy(name, "following");
            break;

        default:
        case PATHBOT_MODE_MANUAL:
            strcpy(name, "manual");
    }
}

bool
mode_update_manual(uint16_t const commands, pathbot_mode_t * const p_mode)
{
    pathbot_mode_t current_mode = *p_mode;

    if (pathbot_mode_is_tracking(current_mode) && commands_has_break(commands))
    {
        *p_mode = PATHBOT_MODE_MANUAL;
    }
    else if (is_detected(current_mode) && commands_has_follow(commands))
    {
        *p_mode = PATHBOT_MODE_FOLLOWING;
    }

    return current_mode != *p_mode;
}

bool
mode_update_tracking(pathbot_coords_t const * const p_coords,
                     pathbot_mode_t * const         p_mode)
{
    pathbot_mode_t current_mode = *p_mode;

    if (is_manual(current_mode) && coords_is_on_route(p_coords))
    {
        *p_mode = PATHBOT_MODE_DETECTED;
    }
    else if (is_detected(current_mode) && !coords_is_on_route(p_coords))
    {
        *p_mode = PATHBOT_MODE_MANUAL;
    }
    else if (pathbot_mode_is_tracking(current_mode) &&
             coords_is_on_finish(p_coords))
    {
        *p_mode = PATHBOT_MODE_MANUAL;
    }
    else if (is_following(current_mode) && !coords_is_on_route(p_coords))
    {
        *p_mode = PATHBOT_MODE_RECOVERING;
    }
    else if (pathbot_mode_is_recovering(current_mode) &&
             coords_is_on_route(p_coords))
    {
        *p_mode = PATHBOT_MODE_FOLLOWING;
    }

    return current_mode != *p_mode;
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
