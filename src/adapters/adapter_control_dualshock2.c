#include <adapters.h>
#include <dualshock2.h>
#include <linebot/command.h>
#include <linebot/port.h>
#include <utils/result.h>

void
adapters_control_init(void)
{
    dualshock2_init();
}

int
adapters_control_read(uint16_t *p_commands)
{
    int result = RESULT_OK;

    uint16_t raw     = DS2_NONE;
    uint16_t command = LINEBOT_COMMAND_NONE;

    if (dualshock2_read(&raw) == RESULT_OK)
    {
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

        *p_commands = command;
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
}