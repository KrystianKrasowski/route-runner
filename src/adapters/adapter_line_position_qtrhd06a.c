#include <core.h>
#include <qtrhd06a.h>

void
core_port_line_position_init(void)
{
    qtrhd06a_init();
}

core_position_t
core_port_line_position_map(uint8_t *raw_position)
{
    core_position_t position;
    position.left   = raw_position[0];
    position.middle = raw_position[1];
    position.right  = raw_position[2];

    return position;
}