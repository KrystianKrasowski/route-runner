#ifndef _CORE_VEHICLE_H
#define _CORE_VEHICLE_H

#include "control.h"
#include "mode.h"
#include "motion.h"
#include "position.h"
#include <stdint.h>

typedef struct core_vehicle
{
    core_control_t  control;
    core_motion_t   motion;
    core_mode_t     mode;
    core_position_t position;
    bool            position_handeled;
    bool            route_guard_timeout;
} core_vehicle_t;

void
core_vehicle_init(core_vehicle_t *self);

core_mode_value_t
core_vehicle_get_mode_value(core_vehicle_t *self);

void
core_vehicle_set_mode_value(core_vehicle_t *self, core_mode_value_t value);

core_mode_t
core_vehicle_get_mode(core_vehicle_t *self);

void
core_vehicle_set_mode(core_vehicle_t *self, core_mode_t mode);

bool
core_vehicle_is_mode_changed(core_vehicle_t *self);

uint16_t
core_vehicle_get_commands(core_vehicle_t *self);

bool
core_vehicle_has_command(core_vehicle_t *self, core_control_command_t command);

int8_t
core_vehicle_position_regulate(core_vehicle_t *self);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_coords(core_vehicle_t *self, core_coords_t coords);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_control(core_vehicle_t *self, core_control_t control);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_mode(core_vehicle_t *self);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_motion(core_vehicle_t *self);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_route_guard(core_vehicle_t *self);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_timeout_route_guard_old(core_vehicle_t *self);

/**
 * @deprecated Distributed state machine. Will be removed in 0.4.x
 */
void
core_vehicle_update_state_indicator(core_vehicle_t *self);

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