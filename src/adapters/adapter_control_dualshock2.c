#include <adapters.h>
#include <linebot/command.h>
#include <linebot/port.h>
#include <dualshock2.h>

void
adapters_control_init(void)
{
    dualshock2_init();
}

uint16_t
adapters_control_map(uint16_t const raw)
{
    uint16_t command = LINEBOT_COMMAND_NONE;

    if (raw & DS2_R2)
    {
        command |= LINEBOT_COMMAND_FORWARD;
    }

    if (raw & DS2_L2)
    {
        command |= LINEBOT_COMMAND_BACKWARD;
    }

    if (raw & DS2_RIGHT)
    {
        command |= LINEBOT_COMMAND_RIGHT;
    }

    if (raw & DS2_LEFT)
    {
        command |= LINEBOT_COMMAND_LEFT;
    }

    if (raw & DS2_CIRCLE)
    {
        command |= LINEBOT_COMMAND_BREAK;
    }

    if (raw & DS2_CROSS)
    {
        command |= LINEBOT_COMMAND_FOLLOW;
    }

    return command;
}