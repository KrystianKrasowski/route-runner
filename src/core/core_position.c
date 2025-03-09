#include "core/position.h"
#include <stdbool.h>
#include <string.h>

#define FULL_ON_LINE  100
#define FULL_OFF_LINE 20

static inline bool
is_stright_on_line(core_position_t *self);

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
    if (is_stright_on_line(self))
    {
        return CORE_POSITION_STRIGHT_ON_LINE;
    }
    else if(is_on_line(self))
    {
        return CORE_POSITION_ON_LINE;
    }
    else
    {
        return CORE_POSITION_NO_LINE;
    }
}

int8_t
core_position_compute_error(core_position_t *self)
{
    return self->right - self->left;
}

uint8_t
core_position_get_by_place(core_position_t *self, core_position_place_t place)
{
    switch(place)
    {
        case CORE_POSITION_PLACE_LEFT_3:
            return self->left;
        case CORE_POSITION_PLACE_LEFT_2:
            return self->left;
        case CORE_POSITION_PLACE_LEFT_1:
            return self->left;
        case CORE_POSITION_PLACE_RIGHT_1:
            return self->middle;
        case CORE_POSITION_PLACE_RIGHT_2:
            return self->middle;
        case CORE_POSITION_PLACE_RIGHT_3:
            return self->right;
        default:
            return 0;
    }
}

static inline bool
is_stright_on_line(core_position_t *self)
{
    return self->middle >= FULL_ON_LINE &&
           (self->left <= FULL_OFF_LINE || self->right <= FULL_OFF_LINE);
}

static inline bool
is_on_line(core_position_t *self)
{
    return self->middle >= FULL_OFF_LINE || self->left >= FULL_OFF_LINE ||
           self->right >= FULL_OFF_LINE;
}