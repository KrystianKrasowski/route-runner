#include "core_remote_control_apply_chain.h"
#include "core/types.h"

static bool
apply_break_for_line_following(core_vehicle_t *vehicle, uint16_t command);

static bool
bypass_any_for_line_following(core_vehicle_t *vehicle, uint16_t command);

static bool
truncate_follow_for_manual(core_vehicle_t *vehicle, uint16_t command);

static bool
apply_any_command(core_vehicle_t *vehicle, uint16_t command);

static inline bool
is_state(core_vehicle_t *vehicle, core_vehicle_state_t state);

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command);

bool
core_remote_control_apply(core_vehicle_t *vehicle, uint16_t command)
{
    return apply_break_for_line_following(vehicle, command) ||
           bypass_any_for_line_following(vehicle, command) ||
           truncate_follow_for_manual(vehicle, command) ||
           apply_any_command(vehicle, command);
}

static bool
apply_break_for_line_following(core_vehicle_t *vehicle, uint16_t command)
{
    if (is_state(vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING) &&
        contains_command(command, CORE_REMOTE_CONTROL_BREAK))
    {
        core_vehicle_set_command(vehicle, CORE_REMOTE_CONTROL_BREAK);
        return true;
    }

    return false;
}

static bool
bypass_any_for_line_following(core_vehicle_t *vehicle, uint16_t command)
{
    if (is_state(vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING) &&
        !contains_command(command, CORE_REMOTE_CONTROL_BREAK))
    {
        core_vehicle_set_command(vehicle, CORE_REMOTE_CONTROL_NONE);
        return true;
    }

    return false;
}

static bool
truncate_follow_for_manual(core_vehicle_t *vehicle, uint16_t command)
{
    if (is_state(vehicle, CORE_VEHICLE_STATE_MANUAL) &&
        contains_command(command, CORE_REMOTE_CONTROL_FOLLOW))
    {
        core_vehicle_set_command(vehicle, command - CORE_REMOTE_CONTROL_FOLLOW);
        return true;
    }

    return false;
}

static bool
apply_any_command(core_vehicle_t *vehicle, uint16_t command)
{
    core_vehicle_set_command(vehicle, command);
    return true;
}

static inline bool
is_state(core_vehicle_t *self, core_vehicle_state_t state)
{
    return core_vehicle_get_state(self) == state;
}

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command)
{
    return remote_control & command;
}