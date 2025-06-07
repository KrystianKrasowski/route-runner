#include <adapters/dump_serial.h>
#include <devices/serial.h>
#include <pathbot/domain.h>
#include <utils/result.h>

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
    (void)mode;
}
