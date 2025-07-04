#include <devices/serial.h>
#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <stdio.h>
#include <string.h>
#include <utils/result.h>

#define MESSAGE_MODE_LENGTH 20
#define MESSAGE_PID_LENGTH  35

void
pathbot_port_dump_mode(pathbot_mode_t const mode)
{
    char mode_name[11];
    memset(mode_name, 0, 10);
    pathbot_mode_get_name(mode, mode_name);

    char message[MESSAGE_MODE_LENGTH];

    snprintf(message, sizeof(message), "MODE: %s\n\r", mode_name);
    device_serial_send(DEVICE_SERIAL_1, message);
}

void
pathbot_port_dump_pid_conf(pathbot_pid_conf_t const *p_pid_conf)
{
    int kp = (int)(p_pid_conf->kp * 100);
    int ki = (int)(p_pid_conf->ki * 100);
    int kd = (int)(p_pid_conf->kd * 100);

    char message[MESSAGE_PID_LENGTH] = "PID:";

    snprintf(
        message, sizeof(message), "PID: kp %d; ki %d; kd %d\n\r", kp, ki, kd);

    device_serial_send(DEVICE_SERIAL_1, message);
}
