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

int
adapters_coords_parse(uint8_t const *p_byte_buffer, linebot_coords_t *coords)
{
    uint8_t p_raw[6];
    qtrhd06a_parse_values(p_byte_buffer, p_raw);

    return linebot_coords_acquire(normalize(p_raw[0]),
                                  normalize(p_raw[1]),
                                  normalize(p_raw[2]),
                                  normalize(p_raw[3]),
                                  normalize(p_raw[4]),
                                  normalize(p_raw[5]),
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