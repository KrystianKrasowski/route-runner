#include <adapters.h>
#include <linebot/port.h>
#include <qtrhd06a.h>

static uint8_t
normalize(uint8_t raw);

void
adapters_coords_init(void)
{
    qtrhd06a_init();
}

linebot_result_t
adapters_coords_map(uint8_t const *raw, linebot_coords_t *coords)
{
    return linebot_coords_acquire(normalize(raw[0]),
                              normalize(raw[1]),
                              normalize(raw[2]),
                              normalize(raw[3]),
                              normalize(raw[4]),
                              normalize(raw[5]),
                              coords);
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