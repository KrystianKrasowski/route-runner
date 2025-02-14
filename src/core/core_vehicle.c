#include "core.h"
#include <string.h>

static inline void
init_state(core_vehicle_t *self);

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    init_state(self);
}

core_vehicle_state_t
core_vehicle_get_state(core_vehicle_t *self)
{
    uint16_t state;
    stack_peek(&self->state, &state);

    return state;
}

void
core_vehicle_set_state(core_vehicle_t *self, core_vehicle_state_t state)
{
    stack_push_rolling(&self->state, (uint16_t)state);
}

bool
core_vehicle_is_state_changed(core_vehicle_t *self)
{
    uint16_t bottom;
    uint16_t top;

    stack_peek_bottom(&self->state, &bottom);
    stack_peek(&self->state, &top);

    return bottom != top || stack_get_length(&self->state) == 1;
}

static inline void
init_state(core_vehicle_t *self)
{
    stack_t state;
    stack_init(&state, 2);
    stack_push(&state, CORE_VEHICLE_STATE_MANUAL);
    
    self->state = state;
}