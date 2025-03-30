#include "core/mode.h"
#include <string.h>

void
core_mode_init(core_mode_t *self)
{
    memset(self, 0, sizeof(*self));

    stack_t value;
    stack_init(&value, 2);
    stack_push(&value, CORE_MODE_MANUAL);

    self->value = value;
}

void
core_mode_set(core_mode_t *self, core_mode_value_t value)
{
    stack_push_rolling(&self->value, value);
}

core_mode_value_t
core_mode_get(core_mode_t *self)
{
    int16_t value;
    stack_peek(&self->value, &value);

    return value;
}

bool
core_mode_changed(core_mode_t *self)
{
    int16_t bottom;
    int16_t top;

    stack_peek_bottom(&self->value, &bottom);
    stack_peek(&self->value, &top);

    return stack_get_length(&self->value) == 1 || bottom != top;
}