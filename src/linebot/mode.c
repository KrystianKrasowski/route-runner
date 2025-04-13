#include "mode.h"
#include "command.h"
#include "coords.h"

bool
linebot_mode_is_manual(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_MANUAL;
}

bool
linebot_mode_is_detected(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_DETECTED;
}

bool
linebot_mode_is_tracking(linebot_mode_t const self)
{
    return linebot_mode_is_following(self) || linebot_mode_is_recovering(self);
}

bool
// cppcheck-suppress staticFunction
linebot_mode_is_following(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_FOLLOWING;
}

bool
linebot_mode_is_recovering(linebot_mode_t const self)
{
    return self == LINEBOT_MODE_RECOVERING;
}

linebot_mode_t
mode_change_by_commands(linebot_mode_t const self, uint16_t const commands)
{
    linebot_mode_t new_mode = self;

    if (linebot_mode_is_detected(self) && command_has_follow(commands))
    {
        new_mode = LINEBOT_MODE_FOLLOWING;
    }
    else if (linebot_mode_is_tracking(self) && command_has_break(commands))
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }

    return new_mode;
}

linebot_mode_t
mode_change_by_coords(linebot_mode_t const self, linebot_coords_t const coords)
{
    linebot_mode_t new_mode = self;

    if (linebot_mode_is_manual(self) && coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_DETECTED;
    }
    else if (linebot_mode_is_detected(self) && !coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }
    else if (linebot_mode_is_tracking(self) && coords_is_on_finish(coords))
    {
        new_mode = LINEBOT_MODE_MANUAL;
    }
    else if (linebot_mode_is_following(self) && !coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_RECOVERING;
    }
    else if (linebot_mode_is_recovering(self) && coords_is_on_route(coords))
    {
        new_mode = LINEBOT_MODE_FOLLOWING;
    }

    return new_mode;
}