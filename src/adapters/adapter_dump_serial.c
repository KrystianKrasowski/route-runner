#include <devices/serial.h>
#include <pathbot/api.h>
#include <pathbot/domain.h>
#include <stdlib.h>
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

    char message[MESSAGE_MODE_LENGTH] = "MODE: ";
    strcat(message, mode_name);
    strcat(message, "\n\r");

    device_serial_send(DEVICE_SERIAL_1, message);
}

void
pathbot_port_dump_pid_conf(pathbot_pid_conf_t const *p_pid_conf)
{
    int kp = (int)(p_pid_conf->kp * 100);
    int ki = (int)(p_pid_conf->ki * 100);
    int kd = (int)(p_pid_conf->kd * 100);

    char int_buffer[4];
    char message[MESSAGE_PID_LENGTH] = "PID:";

    itoa(kp, int_buffer, 10);
    strcat(message, " kp ");
    strcat(message, int_buffer);

    itoa(ki, int_buffer, 10);
    strcat(message, " ki ");
    strcat(message, int_buffer);

    itoa(kd, int_buffer, 10);
    strcat(message, " kd ");
    strcat(message, int_buffer);

    strcat(message, "\n\r");

    device_serial_send(DEVICE_SERIAL_1, message);
}
