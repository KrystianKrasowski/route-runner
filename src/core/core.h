#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>

typedef enum
{
    CORE_MOTION_NONE,
    CORE_MOTION_FORWARD,
    CORE_MOTION_BACKWARD,
} core_motion_direction_t;

typedef struct
{
    core_motion_direction_t direction;
    int8_t                  angle;
} core_motion_t;

typedef enum
{
    CORE_REMOTE_CONTROL_NONE     = 0,
    CORE_REMOTE_CONTROL_FORWARD  = 1,
    CORE_REMOTE_CONTROL_BACKWARD = 2,
    CORE_REMOTE_CONTROL_LEFT     = 4,
    CORE_REMOTE_CONTROL_RIGHT    = 8,
} core_remote_control_t;

typedef struct core_vehicle
{
    uint16_t      command;
    core_motion_t motion;
} core_vehicle_t;

void
core_vehicle_init(core_vehicle_t *self);

void
core_task_remote_control_receive(core_vehicle_t *vehicle);

void
core_task_motion_update(core_vehicle_t *vehicle);

void
core_port_remote_control_init(void);

uint16_t
core_port_remote_control_map(uint16_t raw_command);

void
core_port_motion_init(void);

void
core_port_motion_apply(core_motion_t *motion);

#endif