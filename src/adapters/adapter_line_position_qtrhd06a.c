#include <core.h>
#include <qtrhd06a.h>

static uint8_t
normalize(uint8_t raw_position);

void
core_port_line_position_init(void)
{
    qtrhd06a_init();
}

core_position_t
core_port_line_position_map(uint8_t *raw_position)
{
    core_position_t position;
    position.left   = normalize(raw_position[0]);
    position.middle = normalize(raw_position[1]);
    position.right  = normalize(raw_position[2]);

    return position;
}

static uint8_t
normalize(uint8_t raw_position)
{
    if (raw_position > 110)
    {
        raw_position = 100;
    }

    if (raw_position < 10)
    {
        raw_position = 0;
    }

    return raw_position;
}