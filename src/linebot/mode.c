#include "mode.h"
#include "coords.h"

bool
mode_is_manual(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_MANUAL;
}

bool
mode_is_route_detected(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_DETECTED;
}

bool
mode_is_tracking_route(linebot_mode_t const self)
{
    return mode_is_following_route(self) || mode_is_recovering_route(self);
}

bool
mode_is_following_route(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_FOLLOWING;
}

bool
mode_is_recovering_route(linebot_t const self)
{
    return self == LINEBOT_MODE_RECOVERING;
}

linebot_mode_t
mode_change_by_commands(linebot_mode_t const self, uint16_t const commands)
{
    linebot_mode_t new_mode = self;

    bool is_command_follow = commands & LINEBOT_COMMAND_FOLLOW;
    bool is_command_break  = commands & LINEBOT_COMMAND_BREAK;

    if (mode_is_route_detected(self) && is_command_follow)
    {
        new_mode = LINEBOT_MODE_FOLLOWING;
    }
    else if (mode_is_tracking_route(self) && is_command_break)
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }

    return new_mode;
}

linebot_mode_t
mode_change_by_coords(linebot_mode_t const self, linebot_coords_t const coords)
{
    linebot_mode_t new_mode = self;

    if (mode_is_manual(self) && coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_DETECTED;
    }
    else if (mode_is_route_detected(self) && !coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }
    else if (mode_is_tracking_route(self) && coords_is_on_finish(coords))
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }
    else if (mode_is_following_route(self) && !coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_RECOVERING;
    }
    else if (mode_is_recovering_route(self) && coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_FOLLOWING;
    }

    return new_mode;
}