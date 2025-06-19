#include <devices/qtrhd06a.h>
#include <mappers/qtrhd06a_coords.h>

static inline void
normalize(uint8_t *p_value);

void
mapper_qtrhd06a_coords_read(uint8_t                  raw_values[],
                            uint8_t const            raw_values_size,
                            pathbot_coords_t * const p_coords)
{
    for (uint8_t i = 0; i < raw_values_size; i++)
    {
        normalize(&raw_values[i]);
        p_coords->coords[i] = raw_values[i];
    }
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
