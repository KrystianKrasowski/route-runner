#include "core_vehicle_command_apply.h"
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
is_mode(core_vehicle_t *vehicle, core_mode_t mode);

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command);

bool
core_vehicle_command_apply(core_vehicle_t *vehicle, uint16_t command)
{
    return apply_break_for_line_following(vehicle, command) ||
           bypass_any_for_line_following(vehicle, command) ||
           truncate_follow_for_manual(vehicle, command) ||
           apply_any_command(vehicle, command);
}

static bool
apply_break_for_line_following(core_vehicle_t *vehicle, uint16_t command)
{
    if (is_mode(vehicle, CORE_MODE_LINE_FOLLOWING) &&
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
    if (is_mode(vehicle, CORE_MODE_LINE_FOLLOWING) &&
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
    if (is_mode(vehicle, CORE_MODE_MANUAL) &&
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
is_mode(core_vehicle_t *self, core_mode_t mode)
{
    return core_vehicle_get_mode(self) == mode;
}

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command)
{
    return remote_control & command;
}