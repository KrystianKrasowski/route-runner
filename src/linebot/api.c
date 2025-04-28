#include "command.h"
#include "context.h"
#include "coords.h"
#include "mode.h"
#include "motion_factory.h"
#include "position.h"
#include <errno.h>
#include <linebot/api.h>
#include <linebot/port.h>

static inline void
change_mode_by_control(linebot_t const h_self, uint16_t const commands);

static inline void
apply_manual_motion(linebot_t const h_self, uint16_t const commands);

static inline void
change_mode_by_coords(linebot_t const h_self, linebot_coords_t const h_coords);

static inline void
apply_tracking_motion(linebot_t const h_self, linebot_coords_t const h_coords);

static inline void
stop_immediately(linebot_t const h_self);

void
linebot_init(void)
{
    coords_init();
    position_init();
    linebot_motion_init();
    context_init();
}

int
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const ph_self)
{
    if (coords_validate(coords) < 0)
    {
        return -EINVAL;
    }

    if (context_acquire(mode, coords, errsize, ph_self) < 0)
    {
        return -ENOMEM;
    }

    return 0;
}

void
// cppcheck-suppress unusedFunction
linebot_release(linebot_t const h_self)
{
    context_release(h_self);
}

int
// cppcheck-suppress unusedFunction
linebot_get_mode(linebot_t const h_self, linebot_mode_t * const p_mode)
{
    int result = 0;

    if (context_validate(h_self) >= 0)
    {
        *p_mode = context_get_mode(h_self);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_manual_control(linebot_t const h_self, uint16_t const commands)
{
    int result = 0;

    if (context_validate(h_self) >= 0)
    {
        apply_manual_motion(h_self, commands);
        change_mode_by_control(h_self, commands);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_route_tracking(linebot_t const        h_self,
                              linebot_coords_t const h_coords)
{
    int result = 0;

    if (coords_validate(h_coords) >= 0 && context_validate(h_self) >= 0)
    {
        apply_tracking_motion(h_self, h_coords);
        change_mode_by_coords(h_self, h_coords);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_immediate_stop(linebot_t const h_self)
{
    int result = 0;

    if (context_validate(h_self) >= 0)
    {
        stop_immediately(h_self);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

static inline void
change_mode_by_control(linebot_t const h_self, uint16_t const commands)
{
    linebot_mode_t mode     = context_get_mode(h_self);
    linebot_mode_t new_mode = mode_change_by_commands(mode, commands);

    if (context_update_mode(h_self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }
}

static inline void
apply_manual_motion(linebot_t const h_self, uint16_t const commands)
{
    if (!context_is_tracking_route(h_self) || command_has_break(commands))
    {
        linebot_motion_t h_motion = motion_create_by_commands(commands);

        linebot_port_motion_apply(h_motion);
        linebot_motion_release(h_motion);
    }
}

static inline void
change_mode_by_coords(linebot_t const h_self, linebot_coords_t const h_coords)
{
    linebot_mode_t mode     = context_get_mode(h_self);
    linebot_mode_t new_mode = mode_change_by_coords(mode, h_coords);

    if (context_update_mode(h_self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }
}

static inline void
apply_tracking_motion(linebot_t const h_self, linebot_coords_t const h_coords)
{
    if (context_is_tracking_route(h_self))
    {
        position_t h_position = context_get_position(h_self);
        position_update_coords(h_position, h_coords);

        linebot_motion_t h_motion = motion_create_by_position(h_position);
        linebot_port_motion_apply(h_motion);
        linebot_motion_release(h_motion);
    }
}

static inline void
stop_immediately(linebot_t const h_self)
{
    linebot_mode_t   new_mode = LINEBOT_MODE_MANUAL;
    linebot_motion_t h_motion = motion_create_standby();

    context_update_mode(h_self, new_mode);
    linebot_port_mode_changed(new_mode);
    linebot_port_motion_apply(h_motion);
    linebot_motion_release(h_motion);
}
