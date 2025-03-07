#ifndef _CORE_VEHICLE_H
#define _CORE_VEHICLE_H

#include "motion.h"
#include "position.h"
#include <stdint.h>
#include <stack.h>

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

bool
core_vehicle_is_line_detected(core_vehicle_t *self);

bool
core_vehicle_is_state_changed(core_vehicle_t *self);

void
core_vehicle_set_command(core_vehicle_t *self, uint16_t command);

uint16_t
core_vehicle_get_command(core_vehicle_t *self);

core_motion_direction_t
core_vehicle_get_motion_direction(core_vehicle_t *self);

int8_t
core_vehicle_get_motion_correction(core_vehicle_t *self);

bool
core_vehicle_is_moving_forward(core_vehicle_t *self);

bool
core_vehicle_is_movint_backward(core_vehicle_t *self);

void
core_vehicle_apply_remote_control(core_vehicle_t *self, uint16_t command);

void
core_vehicle_update_state(core_vehicle_t *self);

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self);

#endif