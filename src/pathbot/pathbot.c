#include "mode.h"
#include <pathbot.h>

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t current, uint16_t commands)
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
