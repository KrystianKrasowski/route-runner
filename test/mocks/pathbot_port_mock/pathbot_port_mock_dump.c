#include <pathbot/domain.h>
#include <pathbot/port.h>
#include <pathbot/port_mock_dump.h>
#include <string.h>

typedef struct
{
    pathbot_mode_t mode;
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

pathbot_mode_t
pathbot_port_mock_dump_verify_mode()
{
    return mock.mode;
}
