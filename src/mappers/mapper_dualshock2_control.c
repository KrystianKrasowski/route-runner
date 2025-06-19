#include "mappers/dualshock2_control.h"
#include <devices/dualshock2.h>
#include <pathbot/domain.h>

uint16_t
mapper_dualshock2_control_read(uint16_t dualshock2_state)
{
    uint16_t commands = PATHBOT_COMMAND_NONE;

    if (dualshock2_state & DS2_R2)
    {
        commands |= PATHBOT_COMMAND_FORWARD;
    }

    if (dualshock2_state & DS2_L2)
    {
        commands |= PATHBOT_COMMAND_BACKWARD;
    }

    if (dualshock2_state & DS2_RIGHT)
    {
        commands |= PATHBOT_COMMAND_RIGHT;
    }

    if (dualshock2_state & DS2_LEFT)
    {
        commands |= PATHBOT_COMMAND_LEFT;
    }

    if (dualshock2_state & DS2_CIRCLE)
    {
        commands |= PATHBOT_COMMAND_BREAK;
    }

    if (dualshock2_state & DS2_CROSS)
    {
        commands |= PATHBOT_COMMAND_FOLLOW;
    }

    return commands;
}
