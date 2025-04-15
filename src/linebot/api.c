#include "command.h"
#include "context.h"
#include "coords.h"
#include "mode.h"
#include "motion.h"
#include "motion_factory.h"
#include "position.h"
#include <errno.h>
#include <linebot/api.h>
#include <linebot/port.h>

static inline void
change_mode_by_control(linebot_t const self, uint16_t const commands);

static inline void
apply_manual_motion(linebot_t const self, uint16_t const commands);

static inline void
change_mode_by_coords(linebot_t const self, linebot_coords_t const coords);

static inline void
apply_tracking_motion(linebot_t const self, linebot_coords_t const coords);

static inline void
stop_immediately(linebot_t const self);

void
linebot_init(void)
{
    coords_init();
    position_init();
    motion_init();
    context_init();
}

int
// cppcheck-suppress staticFunction
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    bool b_coords_valid = coords_validate(coords) >= 0;

    if (!b_coords_valid)
    {
        return -EINVAL;
    }

    bool b_acquired = context_acquire(mode, coords, errsize, handle) >= 0;

    if (!b_acquired)
    {
        return -ENOMEM;
    }

    return 0;
}

int
linebot_acquire_default(linebot_t * const handle)
{
    linebot_coords_t coords;
    bool b_acquired = linebot_coords_acquire(0, 0, 0, 0, 0, 0, &coords) >= 0;

    if (!b_acquired)
    {
        return -ENOMEM;
    }

    b_acquired = linebot_acquire(LINEBOT_MODE_MANUAL, coords, 20, handle) >= 0;

    if (!b_acquired)
    {
        return -ENOMEM;
    }

    return 0;
}

void
// cppcheck-suppress unusedFunction
linebot_release(linebot_t const self)
{
    context_release(self);
}

int
// cppcheck-suppress unusedFunction
linebot_get_mode(linebot_t const self, linebot_mode_t * const mode)
{
    int  result          = 0;
    bool b_context_valid = context_validate(self) >= 0;

    if (b_context_valid)
    {
        *mode = context_get_mode(self);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_manual_control(linebot_t const self, uint16_t const commands)
{
    int  result          = 0;
    bool b_context_valid = context_validate(self) >= 0;

    if (b_context_valid)
    {
        change_mode_by_control(self, commands);
        apply_manual_motion(self, commands);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_route_tracking(linebot_t const        self,
                              linebot_coords_t const h_coords)
{
    int  result          = 0;
    bool b_coords_valid  = coords_validate(h_coords) >= 0;
    bool b_context_valid = context_validate(self) >= 0;

    if (b_coords_valid && b_context_valid)
    {
        change_mode_by_coords(self, h_coords);
        apply_tracking_motion(self, h_coords);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

int
linebot_handle_immediate_stop(linebot_t const self)
{
    int  result          = 0;
    bool b_context_valid = context_validate(self) >= 0;

    if (b_context_valid)
    {
        stop_immediately(self);
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}

static inline void
change_mode_by_control(linebot_t const self, uint16_t const commands)
{
    linebot_mode_t mode     = context_get_mode(self);
    linebot_mode_t new_mode = mode_change_by_commands(mode, commands);

    if (context_update_mode(self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }
}

static inline void
apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    if (!context_is_tracking_route(self) || command_has_break(commands))
    {
        linebot_motion_t motion = motion_create_by_commands(commands);

        linebot_port_motion_apply(motion);
        linebot_motion_release(motion);
    }
}

static inline void
change_mode_by_coords(linebot_t const self, linebot_coords_t const coords)
{
    linebot_mode_t mode     = context_get_mode(self);
    linebot_mode_t new_mode = mode_change_by_coords(mode, coords);

    if (context_update_mode(self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }
}

static inline void
apply_tracking_motion(linebot_t const self, linebot_coords_t const coords)
{
    if (context_is_tracking_route(self) || coords_is_on_finish(coords))
    {
        position_t position = context_get_position(self);
        position_update_coords(position, coords);

        linebot_motion_t motion = motion_create_by_position(position);
        linebot_port_motion_apply(motion);
        linebot_motion_release(motion);
    }
}

static inline void
stop_immediately(linebot_t const self)
{
    linebot_mode_t   new_mode = LINEBOT_MODE_MANUAL;
    linebot_motion_t motion   = motion_create_standby();

    context_update_mode(self, new_mode);
    linebot_port_mode_changed(new_mode);
    linebot_port_motion_apply(motion);
    linebot_motion_release(motion);
}