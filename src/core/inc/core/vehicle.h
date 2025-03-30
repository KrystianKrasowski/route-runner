#ifndef _CORE_VEHICLE_H
#define _CORE_VEHICLE_H

#include "motion.h"
#include "position.h"
#include <stdint.h>
#include <utils/stack.h>

typedef enum
{
    CORE_MODE_MANUAL,
    CORE_MODE_LINE_DETECTED,
    CORE_MODE_LINE_FOLLOWING,
} core_mode_value_t;

typedef enum
{
    CORE_VEHICLE_MOTION_CHANGED,
    CORE_VEHICLE_MOTION_REMAINS,
} core_vehicle_result_t;

typedef struct core_vehicle
{
    uint16_t        command;
    core_motion_t   motion;
    stack_t         mode;
    core_position_t position;
} core_vehicle_t;

void
core_vehicle_init(core_vehicle_t *self);

core_mode_value_t
core_vehicle_get_mode_value(core_vehicle_t *self);

void
core_vehicle_set_mode_value(core_vehicle_t *self, core_mode_value_t value);

bool
core_vehicle_is_mode_changed(core_vehicle_t *self);

uint16_t
core_vehicle_get_command(core_vehicle_t *self);

bool
core_vehicle_is_commanded(core_vehicle_t *self, uint16_t command);

void
core_vehicle_update_coords(core_vehicle_t *self, core_coords_t coords);

core_coords_t
core_vehicle_get_coords(core_vehicle_t *self);

int8_t
core_vehicle_last_position_error(core_vehicle_t *self);

int16_t
core_vehicle_get_position_errors_sum(core_vehicle_t *self);

bool
core_vehicle_is_position_updated(core_vehicle_t *self);

void
core_vehicle_set_motion(core_vehicle_t *self, core_motion_t motion);

bool
core_vehicle_motion_differs(core_vehicle_t *self, core_motion_t *motion);

core_motion_direction_t
core_vehicle_get_motion_direction(core_vehicle_t *self);

int8_t
core_vehicle_get_motion_correction(core_vehicle_t *self);

void
core_vehicle_set_motion_direction(core_vehicle_t         *self,
                                  core_motion_direction_t direction);

void
core_vehicle_set_motion_correction(core_vehicle_t *self, int8_t correction);

bool
core_vehicle_is_moving_forward(core_vehicle_t *self);

bool
core_vehicle_is_moving_backward(core_vehicle_t *self);

void
core_vehicle_update_command(core_vehicle_t *self, uint16_t command);

void
core_vehicle_update_mode(core_vehicle_t *self);

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self);

int8_t
core_vehicle_update_position_error(core_vehicle_t *self);

#endif