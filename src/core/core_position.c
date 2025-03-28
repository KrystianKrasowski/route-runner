#include "core/position.h"
#include <stdbool.h>
#include <string.h>

static int8_t const coordinate_weights[CORE_POSITION_COORDS_SIZE] = {
    -100, -40, -20, 20, 40, 100};

static inline bool
is_on_line(core_position_t *self);

void
core_position_init(core_position_t *self)
{
    memset(self, 0, sizeof(*self));
}

core_position_status_t
core_position_get_status(core_position_t *self)
{
    if (is_on_line(self))
    {
        return CORE_POSITION_ON_LINE;
    }
    else
    {
        return CORE_POSITION_OFF_LINE;
    }
}

core_position_status_t
core_position_compute_error(core_position_t *self, int8_t *error)
{
    int16_t sum        = 0;
    int16_t weight_sum = 0;

    for (uint8_t i = 0; i < CORE_POSITION_COORDS_SIZE; i++)
    {
        sum += self->coordinates[i];
        weight_sum += coordinate_weights[i] * self->coordinates[i];
    }

    if (sum == 0)
    {
        return CORE_POSITION_OFF_LINE;
    }

    *error = weight_sum / sum;

    return CORE_POSITION_ON_LINE;
}

uint8_t
core_position_get_by_place(core_position_t *self, core_position_place_t place)
{
    return self->coordinates[place];
}

void
core_position_set_by_place(core_position_t      *self,
                           core_position_place_t place,
                           uint8_t               position)
{
    self->coordinates[place] = position;
}

bool
core_position_equals(core_position_t *self, core_position_t *other)
{
    for (uint8_t i = 0; i < CORE_POSITION_COORDS_SIZE; i++)
    {
        if (self->coordinates[i] != other->coordinates[i])
        {
            return false;
        }
    }

    return true;
}

static inline bool
is_on_line(core_position_t *self)
{
    for (uint8_t i = 0; i < CORE_POSITION_COORDS_SIZE; i++)
    {
        if (self->coordinates[i] >= CORE_POSITION_DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}