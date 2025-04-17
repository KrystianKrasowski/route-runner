#include <adapters.h>
#include <dualshock2.h>
#include <linebot/command.h>
#include <linebot/port.h>

void
adapters_control_init(void)
{
    dualshock2_init();
}

uint16_t
adapters_control_parse(uint8_t const *p_byte_buffer)
{
    uint16_t raw     = dualshock2_parse_commands(p_byte_buffer);
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