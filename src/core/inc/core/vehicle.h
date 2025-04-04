#ifndef _CORE_VEHICLE_H
#define _CORE_VEHICLE_H

#include "control.h"
#include "mode.h"
#include "motion.h"
#include "position.h"
#include <stdint.h>

typedef struct core_vehicle
{
    core_mode_t     mode;
    core_position_t position;
} core_vehicle_t;

void
core_vehicle_init(core_vehicle_t *self);

core_mode_t
core_vehicle_get_mode(core_vehicle_t *self);

void
core_vehicle_set_mode(core_vehicle_t *self, core_mode_t mode);

void
core_vehicle_apply_manual_motion(core_vehicle_t *self, core_control_t control);

void
core_vehicle_apply_following_motion(core_vehicle_t *self, core_coords_t coords);

void
core_vehicle_timeout_route_guard(core_vehicle_t *self);

void
core_vehicle_change_mode_by_control(core_vehicle_t *self,
                                    core_control_t  control);

void
core_vehicle_change_mode_by_coords(core_vehicle_t *self, core_coords_t coords);

#endif