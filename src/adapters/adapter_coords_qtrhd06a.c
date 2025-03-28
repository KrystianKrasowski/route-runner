#include <core/coords.h>
#include <core/ports.h>
#include <qtrhd06a.h>

static uint8_t
normalize(uint8_t raw);

void
core_port_coords_init(void)
{
    qtrhd06a_init();
}

core_coords_t
core_port_coords_map(uint8_t *raw)
{
    core_coords_t coords;

    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_3, normalize(raw[0]));
    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_2, normalize(raw[1]));
    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_1, normalize(raw[2]));
    core_coords_set_place(
        &coords, CORE_COORDS_PLACE_RIGHT_1, normalize(raw[3]));
    core_coords_set_place(
        &coords, CORE_COORDS_PLACE_RIGHT_2, normalize(raw[4]));
    core_coords_set_place(
        &coords, CORE_COORDS_PLACE_RIGHT_3, normalize(raw[5]));

    return coords;
}

static uint8_t
normalize(uint8_t raw)
{
    if (raw > 120)
    {
        raw = 120;
    }

    if (raw < 20)
    {
        raw = 20;
    }

    return raw - 20;
}