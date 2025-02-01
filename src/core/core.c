#include "core.h"
#include <string.h>

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
}