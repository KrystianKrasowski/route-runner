#include "coords.h"

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

int8_t
coords_compute_mass_center(pathbot_coords_t const * const p_self)
{
    int8_t  mass_center = 0;
    int16_t sum         = 0;
    int16_t weight_sum  = 0;

    for (uint8_t i = 0; i < p_self->length; i++)
    {
        sum += p_self->coords[i];
        weight_sum += (p_self->weights[i] * p_self->coords[i]);
    }

    if (sum != 0)
    {
        mass_center = weight_sum / sum;
    }

    return mass_center;
}
