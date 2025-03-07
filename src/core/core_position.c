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