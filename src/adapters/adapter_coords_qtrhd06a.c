#include <adapters.h>
#include <errno.h>
#include <linebot/port.h>
#include <qtrhd06a.h>
#include <utils/result.h>

static uint8_t
normalize(uint8_t raw);

void
adapters_coords_init(void)
{
    qtrhd06a_init();
}

int
adapters_coords_read(linebot_coords_t *ph_coords)
{
    int result = RESULT_OK;

    uint8_t raw[6];

    if (qtrhd06a_read(raw) == RESULT_OK)
    {
        uint8_t l3 = normalize(raw[0]);
        uint8_t l2 = normalize(raw[1]);
        uint8_t l1 = normalize(raw[2]);
        uint8_t r1 = normalize(raw[3]);
        uint8_t r2 = normalize(raw[4]);
        uint8_t r3 = normalize(raw[5]);

        if (linebot_coords_acquire(l3, l2, l1, r1, r2, r3, ph_coords) < 0)
        {
            result = -ENOMEM;
        }
    }
    else
    {
        result = RESULT_NOT_READY;
    }

    return result;
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