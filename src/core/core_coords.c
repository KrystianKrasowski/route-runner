#include "core/coords.h"
#include <string.h>

static int8_t const COORDS_WEIGHTS[CORE_COORDS_SIZE] = {
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

void
core_coords_compute_mass_center(core_coords_t *self, int8_t *error)
{
    int16_t sum        = 0;
    int16_t weight_sum = 0;

    for (uint8_t i = 0; i < CORE_COORDS_SIZE; i++)
    {
        sum += self->coordinates[i];
        weight_sum += COORDS_WEIGHTS[i] * self->coordinates[i];
    }

    if (sum != 0)
    {
        *error = weight_sum / sum;
    }

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
core_coords_is_on_route(core_coords_t *self)
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

bool
core_coords_is_on_finish(core_coords_t *self)
{
    return self->coordinates[0] >= CORE_COORDS_LINE_DETECTION_TRESHOLD &&
           self->coordinates[2] < CORE_COORDS_LINE_DETECTION_TRESHOLD &&
           self->coordinates[3] < CORE_COORDS_LINE_DETECTION_TRESHOLD &&
           self->coordinates[5] >= CORE_COORDS_LINE_DETECTION_TRESHOLD;
}