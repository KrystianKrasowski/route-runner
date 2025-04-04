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
    return core_coords(normalize(raw[0]),
                       normalize(raw[1]),
                       normalize(raw[2]),
                       normalize(raw[3]),
                       normalize(raw[4]),
                       normalize(raw[5]));
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