#ifndef _CORE_POSITION_REGULATOR_H
#define _CORE_POSITION_REGULATOR_H

#include "core/position.h"
#include <stdint.h>

int8_t
core_position_regulate_pid(core_position_t *position);

#endif