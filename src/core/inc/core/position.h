#ifndef _CORE_POSITION_H
#define _CORE_POSITION_H

#include <stdint.h>

typedef struct
{
    uint8_t left;
    uint8_t middle;
    uint8_t right;
} core_position_t;

typedef enum
{
    CORE_POSITION_NO_LINE,
    CORE_POSITION_STRIGHT_ON_LINE,
    CORE_POSITION_ON_LINE,
} core_position_status_t;

void
core_position_init(core_position_t *self);

core_position_status_t
core_position_get_status(core_position_t *self);

#endif