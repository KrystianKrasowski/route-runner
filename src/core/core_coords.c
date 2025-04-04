#include "core/coords.h"
#include <string.h>

static int8_t const coordinate_weights[CORE_COORDS_SIZE] = {
    -100, -40, -20, 20, 40, 100};

core_coords_t
core_coords(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3)
{
    core_coords_t coords;
    memset(&coords, 0, sizeof(coords));
    coords.coordinates[0] = l3;
    coords.coordinates[1] = l2;
    coords.coordinates[2] = l1;
    coords.coordinates[3] = r1;
    coords.coordinates[4] = r2;
    coords.coordinates[5] = r3;
    return coords;
}

core_coords_status_t
core_coords_get_status(core_coords_t *self)
{
    if (core_coords_are_on_route(self))
    {
        return CORE_COORDS_STATUS_ON_ROUTE;
    }
    else
    {
        return CORE_COORDS_STATUS_OFF_LINE;
    }
}

core_coords_status_t
core_coords_compute_mass_center(core_coords_t *self, int8_t *error)
{
    int16_t sum        = 0;
    int16_t weight_sum = 0;

    for (uint8_t i = 0; i < CORE_COORDS_SIZE; i++)
    {
        sum += self->coordinates[i];
        weight_sum += coordinate_weights[i] * self->coordinates[i];
    }

    if (sum == 0)
    {
        return CORE_COORDS_STATUS_OFF_LINE;
    }

    *error = weight_sum / sum;

    return CORE_COORDS_STATUS_ON_ROUTE;
}

bool
core_coords_equals(core_coords_t *self, core_coords_t *other)
{
    for (uint8_t i = 0; i < CORE_COORDS_SIZE; i++)
    {
        if (self->coordinates[i] != other->coordinates[i])
        {
            return false;
        }
    }

    return true;
}

bool
core_coords_are_on_route(core_coords_t *self)
{
    for (uint8_t i = 0; i < CORE_COORDS_SIZE; i++)
    {
        if (self->coordinates[i] >= CORE_COORDS_LINE_DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}