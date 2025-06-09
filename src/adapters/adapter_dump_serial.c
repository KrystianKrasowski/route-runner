#include <adapters/dump_serial.h>
#include <devices/serial.h>
#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <stdio.h>
#include <string.h>
#include <utils/result.h>

#define MESSAGE_MODE_LENGTH 20
#define MESSAGE_PID_LENGTH  35

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
    char message[MESSAGE_MODE_LENGTH];

    memset(mode_name, 0, 10);
    memset(message, 0, MESSAGE_MODE_LENGTH);

    pathbot_mode_get_name(mode, mode_name);
    sprintf(message, "MODE: %s\n\r", mode_name);

    device_serial_send(DEVICE_SERIAL_1, message);
}

void
pathbot_port_dump_pid_conf(pathbot_pid_conf_t const *p_pid_conf)
{
    char message[MESSAGE_PID_LENGTH];
    int  kp = (int)(p_pid_conf->kp * 100);
    int  ki = (int)(p_pid_conf->ki * 100);
    int  kd = (int)(p_pid_conf->kd * 100);

    sprintf(message, "PID: kp %d; ki %d; kd %d\n\r", kp, ki, kd);

    device_serial_send(DEVICE_SERIAL_1, message);
}
