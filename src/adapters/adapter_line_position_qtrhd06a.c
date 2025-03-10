#include <core/ports.h>
#include <core/position.h>
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
    
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_LEFT_3, normalize(raw_position[0]));
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_LEFT_2, normalize(raw_position[1]));
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_LEFT_1, normalize(raw_position[2]));
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_RIGHT_1, normalize(raw_position[3]));
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_RIGHT_2, normalize(raw_position[4]));
    core_position_set_by_place(
        &position, CORE_POSITION_PLACE_RIGHT_3, normalize(raw_position[5]));

    return position;
}

static uint8_t
normalize(uint8_t raw_position)
{
    if (raw_position > 120)
    {
        raw_position = 120;
    }

    if (raw_position < 20)
    {
        raw_position = 20;
    }

    return raw_position - 20;
}