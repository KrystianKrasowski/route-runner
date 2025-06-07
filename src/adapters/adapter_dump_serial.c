#include <adapters/dump_serial.h>
#include <devices/serial.h>
#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <stdio.h>
#include <string.h>
#include <utils/result.h>

#define MESSAGE_LENGTH_MODE 19

int
adapter_domain_dump_request_read(void)
{
    if (device_serial_read(DEVICE_SERIAL_1, 'd') == RESULT_OK)
    {
        return RESULT_OK;
    }

    return RESULT_NOT_READY;
}

void
pathbot_port_dump_mode(pathbot_mode_t const mode)
{
    char mode_name[11];
    char message[MESSAGE_LENGTH_MODE];

    memset(mode_name, 0, 10);
    memset(message, 0, MESSAGE_LENGTH_MODE);

    pathbot_mode_get_name(mode, mode_name);
    sprintf(message, "MODE: %s\n", mode_name);

    device_serial_write(DEVICE_SERIAL_1, message, MESSAGE_LENGTH_MODE);
}
