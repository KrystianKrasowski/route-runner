#include <adapters/control_dualshock2.h>
#include <devices/dualshock2.h>
#include <linebot/command.h>
#include <stdint.h>
#include <utils/result.h>

int
adapter_control_dualshock2_read(device_dualshock2_t const h_dualshock,
                                uint16_t                 *p_commands)
{
    int result = RESULT_OK;

    uint16_t raw      = DS2_NONE;
    uint16_t commands = LINEBOT_COMMAND_NONE;

    if (RESULT_OK == device_dualshock2_read(h_dualshock, &raw))
    {
        if (raw & DS2_R2)
        {
            commands |= LINEBOT_COMMAND_FORWARD;
        }

        if (raw & DS2_L2)
        {
            commands |= LINEBOT_COMMAND_BACKWARD;
        }

        if (raw & DS2_RIGHT)
        {
            commands |= LINEBOT_COMMAND_RIGHT;
        }

        if (raw & DS2_LEFT)
        {
            commands |= LINEBOT_COMMAND_LEFT;
        }

        if (raw & DS2_CIRCLE)
        {
            commands |= LINEBOT_COMMAND_BREAK;
        }

        if (raw & DS2_CROSS)
        {
            commands |= LINEBOT_COMMAND_FOLLOW;
        }

        *p_commands = commands;
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
}
