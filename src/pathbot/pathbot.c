#include "coords.h"
#include "mode.h"
#include <pathbot.h>

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t const current,
                           uint16_t const       commands)
{
    if (mode_is_tracking(current) && commands & PATHBOT_COMMAND_BREAK)
    {
        return PATHBOT_MODE_MANUAL;
    }

    if (mode_is_detected(current) && commands & PATHBOT_COMMAND_FOLLOW)
    {
        return PATHBOT_MODE_FOLLOWING;
    }

    return current;
}

pathbot_mode_t
pathbot_update_mode_tracking(pathbot_mode_t const    current,
                             pathbot_coords_t const *p_coords)
{
    if (mode_is_manual(current) && coords_is_on_route(p_coords))
    {
        return PATHBOT_MODE_DETECTED;
    }

    if (mode_is_detected(current) && !coords_is_on_route(p_coords))
    {
        return PATHBOT_MODE_MANUAL;
    }

    if (mode_is_following(current) && !coords_is_on_route(p_coords))
    {
        return PATHBOT_MODE_RECOVERING;
    }

    if (mode_is_tracking(current) && coords_is_on_finish(p_coords))
    {
        return PATHBOT_MODE_MANUAL;
    }

    if (mode_is_recovering(current) && coords_is_on_route(p_coords))
    {
        return PATHBOT_MODE_FOLLOWING;
    }

    return current;
}
