#include <pathbot/domain.h>
#include <pathbot/port.h>
#include <pathbot/port_mock_dump.h>
#include <string.h>

typedef struct
{
    pathbot_mode_t     mode;
    pathbot_pid_conf_t pid_conf;
} pathbot_mock_dump_t;

static pathbot_mock_dump_t mock;

void
pathbot_port_mock_dump_reset(void)
{
    memset(&mock, 0, sizeof(mock));
}

void
pathbot_port_dump_mode(pathbot_mode_t const mode)
{
    mock.mode = mode;
}

void
pathbot_port_dump_pid_conf(pathbot_pid_conf_t const *p_pid_conf)
{
    memcpy(&mock.pid_conf, p_pid_conf, sizeof(mock.pid_conf));
}

pathbot_mode_t
pathbot_port_mock_dump_verify_mode()
{
    return mock.mode;
}

float
pathbot_port_mock_dump_verify_pid_kp(void)
{
    return mock.pid_conf.kp;
}

float
pathbot_port_mock_dump_verify_pid_ki(void)
{
    return mock.pid_conf.ki;
}

float
pathbot_port_mock_dump_verify_pid_kd(void)
{
    return mock.pid_conf.kd;
}
