#include <adapters/control_dualshock2.h>
#include <devices/dualshock2.h>
#include <pathbot/domain.h>
#include <stdint.h>
#include <utils/result.h>

int
adapter_control_dualshock2_read(device_dualshock2_t const h_dualshock,
                                uint16_t                 *p_commands)
{
    int result = RESULT_OK;

    uint16_t raw      = DS2_NONE;
    uint16_t commands = PATHBOT_COMMAND_NONE;

    if (RESULT_OK == device_dualshock2_read(h_dualshock, &raw))
    {
        if (raw & DS2_R2)
        {
            commands |= PATHBOT_COMMAND_FORWARD;
        }

        if (raw & DS2_L2)
        {
            commands |= PATHBOT_COMMAND_BACKWARD;
        }

        if (raw & DS2_RIGHT)
        {
            commands |= PATHBOT_COMMAND_RIGHT;
        }

        if (raw & DS2_LEFT)
        {
            commands |= PATHBOT_COMMAND_LEFT;
        }

        if (raw & DS2_CIRCLE)
        {
            commands |= PATHBOT_COMMAND_BREAK;
        }

        if (raw & DS2_CROSS)
        {
            commands |= PATHBOT_COMMAND_FOLLOW;
        }

        *p_commands = commands;
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
}
