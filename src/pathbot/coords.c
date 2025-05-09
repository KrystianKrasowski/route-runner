#include "coords.h"
#include <stdint.h>

#define COORDS_DETECTION_TRESHOLD 3

bool
coords_is_on_route(pathbot_coords_t const *p_self)
{
    for (uint8_t i = 0; i < p_self->length; i++)
    {
        if (p_self->coords[i] >= COORDS_DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}

bool
coords_is_on_finish(pathbot_coords_t const *p_self)
{
    uint8_t last_ix = p_self->length - 1;
    uint8_t mid_ix  = p_self->length / 2;

    bool b_1st_on_route  = p_self->coords[0] >= COORDS_DETECTION_TRESHOLD;
    bool b_last_on_route = p_self->coords[last_ix] >= COORDS_DETECTION_TRESHOLD;
    bool b_mid_off_route = false;

    if (p_self->length % 2 == 0)
    {
        b_mid_off_route =
            p_self->coords[mid_ix] < COORDS_DETECTION_TRESHOLD &&
            p_self->coords[mid_ix - 1] < COORDS_DETECTION_TRESHOLD;
    }
    else
    {
        b_mid_off_route =
            p_self->coords[mid_ix + 1] < COORDS_DETECTION_TRESHOLD &&
            p_self->coords[mid_ix] < COORDS_DETECTION_TRESHOLD &&
            p_self->coords[mid_ix - 1] < COORDS_DETECTION_TRESHOLD;
    }

    return b_1st_on_route && b_mid_off_route && b_last_on_route;
}
