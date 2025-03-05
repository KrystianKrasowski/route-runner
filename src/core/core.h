#ifndef _CORE_H
#define _CORE_H

#include <stack.h>
#include <stdbool.h>
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
    int8_t                  correction;
} core_motion_t;

typedef enum
{
    CORE_REMOTE_CONTROL_NONE     = 0,
    CORE_REMOTE_CONTROL_FORWARD  = 1,
    CORE_REMOTE_CONTROL_BACKWARD = 2,
    CORE_REMOTE_CONTROL_LEFT     = 4,
    CORE_REMOTE_CONTROL_RIGHT    = 8,
    CORE_REMOTE_CONTROL_BREAK    = 16,
    CORE_REMOTE_CONTROL_FOLLOW   = 32,
} core_remote_control_t;

typedef enum
{
    CORE_VEHICLE_STATE_MANUAL,
    CORE_VEHICLE_STATE_LINE_DETECTED,
    CORE_VEHICLE_STATE_LINE_FOLLOWING,
} core_vehicle_state_t;

typedef enum
{
    CORE_VEHICLE_MOTION_CHANGED,
    CORE_VEHICLE_MOTION_REMAINS,
} core_vehicle_result_t;

typedef struct
{
    uint8_t left;
    uint8_t middle;
    uint8_t right;
} core_position_t;

typedef struct core_vehicle
{
    uint16_t        command;
    core_motion_t   motion;
    stack_t         state;
    core_position_t position;
} core_vehicle_t;

void
core_vehicle_init(core_vehicle_t *self);

core_vehicle_state_t
core_vehicle_get_state(core_vehicle_t *self);

void
core_vehicle_set_state(core_vehicle_t *self, core_vehicle_state_t state);

void
core_vehicle_set_line_position(core_vehicle_t *self, core_position_t position);

core_position_t
core_vehicle_get_line_position(core_vehicle_t *self);

bool
core_vehicle_is_line_detected(core_vehicle_t *self);

bool
core_vehicle_is_state_changed(core_vehicle_t *self);

void
core_vehicle_set_command(core_vehicle_t *self, uint16_t command);

uint16_t
core_vehicle_get_command(core_vehicle_t *self);

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self);

void
core_motion_init(core_motion_t *self);

bool
core_motion_equals(core_motion_t *self, core_motion_t *other);

void
core_task_remote_control_receive(core_vehicle_t *vehicle);

void
core_task_line_position_receive(core_vehicle_t *vehicle);

void
core_task_vehicle_state_update(core_vehicle_t *vehicle);

void
core_task_motion_update(core_vehicle_t *vehicle);

void
core_task_state_indicator_update(core_vehicle_t *vehicle);

void
core_port_remote_control_init(void);

uint16_t
core_port_remote_control_map(uint16_t raw_command);

void
core_port_line_position_init(void);

core_position_t
core_port_line_position_map(uint8_t *raw_position);

void
core_port_motion_init(void);

void
core_port_motion_apply(core_motion_t *motion);

void
core_port_state_indicator_init(void);

void
core_port_state_indicator_apply(core_vehicle_state_t state);

#endif