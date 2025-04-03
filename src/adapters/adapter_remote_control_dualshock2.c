#include <core.h>
#include <dualshock2.h>

void
core_port_control_init(void)
{
    dualshock2_init();
}

uint16_t
core_port_control_command_map(uint16_t raw_command)
{
    uint16_t command = CORE_CONTROL_NONE;

    if (raw_command & DS2_R2)
    {
        command |= CORE_CONTROL_FORWARD;
    }

    if (raw_command & DS2_L2)
    {
        command |= CORE_CONTROL_BACKWARD;
    }

    if (raw_command & DS2_RIGHT)
    {
        command |= CORE_CONTROL_RIGHT;
    }

    if (raw_command & DS2_LEFT)
    {
        command |= CORE_CONTROL_LEFT;
    }

    if (raw_command & DS2_CIRCLE)
    {
        command |= CORE_CONTROL_BREAK;
    }

    if (raw_command & DS2_CROSS)
    {
        command |= CORE_CONTROL_FOLLOW;
    }

    return command;
}