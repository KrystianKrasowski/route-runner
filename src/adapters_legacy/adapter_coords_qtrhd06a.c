#include <adapters.h>
#include <errno.h>
#include <linebot/port.h>
#include <qtrhd06a.h>
#include <string.h>
#include <utils/result.h>

#define COORDS_SIZE 6

static uint8_t
normalize(uint8_t raw);

void
adapters_coords_init(void)
{
    qtrhd06a_init();
}

int
adapters_coords_create_default(linebot_coords_t *ph_coords)
{
    uint8_t coords[COORDS_SIZE];

    memset(coords, 0, sizeof(coords));

    if (linebot_coords_acquire(coords, COORDS_SIZE, ph_coords) < 0)
    {
        return -ENOMEM;
    }
    
    return RESULT_OK;
}

int
adapters_coords_read(linebot_coords_t *ph_coords)
{
    uint8_t raw[COORDS_SIZE];

    if (qtrhd06a_read(raw) != RESULT_OK)
    {
        return RESULT_NOT_READY;
    }

    uint8_t coords[COORDS_SIZE];

    for (uint8_t i = 0; i < COORDS_SIZE; i++)
    {
        coords[i] = normalize(raw[i]);
    }

    if (linebot_coords_acquire(coords, COORDS_SIZE, ph_coords) < 0)
    {
        return -ENOMEM;
    }

    return RESULT_OK;
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
