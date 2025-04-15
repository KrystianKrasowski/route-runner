#include "command.h"
#include "context.h"
#include "coords.h"
#include "mode.h"
#include "motion.h"
#include "motion_factory.h"
#include "position.h"
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
stop(linebot_t const self);

void
linebot_init(void)
{
    coords_init();
    position_init();
    motion_init();
    context_init();
}

linebot_result_t
// cppcheck-suppress staticFunction
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    linebot_result_t result;

    if (coords_is_valid(coords, &result))
    {
        result = context_acquire(mode, coords, errsize, handle);
    }

    return result;
}

linebot_result_t
linebot_acquire_default(linebot_t * const handle)
{
    linebot_coords_t coords;
    linebot_result_t result = linebot_coords_acquire(0, 0, 0, 0, 0, 0, &coords);

    if (LINEBOT_OK == result)
    {
        result = linebot_acquire(LINEBOT_MODE_MANUAL, coords, 20, handle);
    }

    return result;
}

void
// cppcheck-suppress unusedFunction
linebot_release(linebot_t const self)
{
    context_release(self);
}

linebot_result_t
// cppcheck-suppress unusedFunction
linebot_get_mode(linebot_t const self, linebot_mode_t * const mode)
{
    linebot_result_t result;

    if (context_is_valid(self, &result))
    {
        *mode = context_get_mode(self);
    }

    return result;
}

linebot_result_t
linebot_handle_manual_control(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result;

    if (context_is_valid(self, &result))
    {
        change_mode_by_control(self, commands);
        apply_manual_motion(self, commands);
    }

    return result;
}

linebot_result_t
linebot_handle_route_tracking(linebot_t const        self,
                              linebot_coords_t const coords)
{
    linebot_result_t result;

    if (context_is_valid(self, &result) && coords_is_valid(coords, &result))
    {
        change_mode_by_coords(self, coords);
        apply_tracking_motion(self, coords);
    }

    return result;
}

linebot_result_t
linebot_stop(linebot_t const self)
{
    linebot_result_t result;

    if (context_is_valid(self, &result))
    {
        stop(self);
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
stop(linebot_t const self)
{
    linebot_mode_t   new_mode = LINEBOT_MODE_MANUAL;
    linebot_motion_t motion   = motion_create_standby();

    context_update_mode(self, new_mode);
    linebot_port_mode_changed(new_mode);
    linebot_port_motion_apply(motion);
    linebot_motion_release(motion);
}