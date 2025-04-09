#include <linebot/command.h>
#include <linebot/port.h>
#include <dualshock2.h>

void
linebot_port_control_init(void)
{
    dualshock2_init();
}

uint16_t
linebot_port_control_command_map(uint16_t const raw_command)
{
    uint16_t command = LINEBOT_COMMAND_NONE;

    if (raw_command & DS2_R2)
    {
        command |= LINEBOT_COMMAND_FORWARD;
    }

    if (raw_command & DS2_L2)
    {
        command |= LINEBOT_COMMAND_BACKWARD;
    }

    if (raw_command & DS2_RIGHT)
    {
        command |= LINEBOT_COMMAND_RIGHT;
    }

    if (raw_command & DS2_LEFT)
    {
        command |= LINEBOT_COMMAND_LEFT;
    }

    if (raw_command & DS2_CIRCLE)
    {
        command |= LINEBOT_COMMAND_BREAK;
    }

    if (raw_command & DS2_CROSS)
    {
        command |= LINEBOT_COMMAND_FOLLOW;
    }

    return command;
}