#ifndef _CORE_INTERFACE_H
#define _CORE_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    CORE_VEHICLE_STATE_STANDBY,
    CORE_VEHICLE_STATE_READY,
    CORE_VEHICLE_STATE_RUNNING,
    CORE_VEHICLE_STATE_ERROR,
} core_state_t;

typedef enum
{
    CORE_COMMAND_NONE,
    CORE_COMMAND_RESET,
    CORE_COMMAND_RUN,
    CORE_COMMAND_SPEED_UP,
    CORE_COMMAND_SPEED_DOWN,
} core_command_t;

typedef enum
{
    CORE_CONTROL_DIRECTION_STRIGHT,
    CORE_CONTROL_DIRECTION_LEFT,
    CORE_CONTROL_DIRECTION_RIGHT,
} core_control_direction_t;

typedef struct
{
    core_control_direction_t direction;
    uint8_t                  angle;
} core_control_t;

bool
core_is_line_detected(void);

core_control_t
core_read_control(void);

core_command_t
core_read_command(void);

void
core_set_diagnostics(core_state_t state);

void
core_run(core_control_t control);

void
core_stop(void);

#endif