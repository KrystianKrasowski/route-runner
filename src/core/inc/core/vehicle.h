#ifndef _CORE_VEHICLE_H
#define _CORE_VEHICLE_H

#include "control.h"
#include "mode.h"
#include "motion.h"
#include "position.h"
#include <stdint.h>

typedef enum
{
    CORE_VEHICLE_MOTION_CHANGED,
    CORE_VEHICLE_MOTION_REMAINS,
} core_vehicle_result_t;

typedef struct core_vehicle
{
    core_control_t  control;
    core_motion_t   motion;
    core_mode_t     mode;
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
core_vehicle_get_commands(core_vehicle_t *self);

void
core_vehicle_update_coords(core_vehicle_t *self, core_coords_t coords);

void
core_vehicle_update_control(core_vehicle_t *self, core_control_t control);

void
core_vehicle_update_mode(core_vehicle_t *self);

core_vehicle_result_t
core_vehicle_create_motion(core_vehicle_t *self, core_motion_t *result);

#endif