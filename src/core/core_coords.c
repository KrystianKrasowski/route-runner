#include "core/coords.h"
#include <stdbool.h>
#include <string.h>

static int8_t const coordinate_weights[CORE_COORDS_SIZE] = {
    -100, -40, -20, 20, 40, 100};

static inline bool
is_on_route(core_coords_t *self);

core_coords_t
core_coords_create(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3)
{
    core_coords_t coords;
    core_coords_init(&coords);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_3, l3);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_2, l2);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_LEFT_1, l1);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_RIGHT_1, r1);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_RIGHT_2, r2);
    core_coords_set_place(&coords, CORE_COORDS_PLACE_RIGHT_3, r3);
    return coords;
}

void
core_coords_init(core_coords_t *self)
{
    memset(self, 0, sizeof(*self));
}

core_coords_status_t
core_coords_get_status(core_coords_t *self)
{
    if (is_on_route(self))
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

uint8_t
core_coords_get_place(core_coords_t *self, core_coords_place_t place)
{
    return self->coordinates[place];
}

void
core_coords_set_place(core_coords_t      *self,
                      core_coords_place_t place,
                      uint8_t             value)
{
    self->coordinates[place] = value;
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

static inline bool
is_on_route(core_coords_t *self)
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