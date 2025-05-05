#include <adapters/coords_qtrhd06a.h>
#include <errno.h>
#include <stdint.h>
#include <utils/result.h>

static inline void
normalize(uint8_t *p_value);

int
adapter_coords_qtrhd06a_read(device_qtrhd06a_t const h_device,
                             linebot_coords_t       *ph_coords)
{
    uint8_t coords_size = DEVICE_QTRHD06A_VALUES_LENGTH;
    uint8_t values[coords_size];

    if (device_qtrhd06a_read(h_device, values) != RESULT_OK)
    {
        return RESULT_NOT_READY;
    }

    for (uint8_t i = 0; i < coords_size; i++)
    {
        normalize(&values[i]);
    }

    if (linebot_coords_acquire(values, coords_size, ph_coords))
    {
        return -ENOMEM;
    }

    return RESULT_OK;
}

static inline void
normalize(uint8_t *p_value)
{
    if (*p_value > 120)
    {
        *p_value = 120;
    }

    if (*p_value < 20)
    {
        *p_value = 20;
    }

    *p_value -= 20;
}
