#include "coords.h"
#include "mode.h"
#include "motion.h"
#include "motion_factory.h"
#include "position.h"
#include <linebot.h>
#include <string.h>
#include <utils/pool.h>

typedef struct
{
    linebot_mode_t mode;
    position_t     position;
} linebot_instance_t;

POOL_DECLARE(linebot, linebot_instance_t, 1)

static linebot_pool_t pool;

static linebot_result_t
set_mode(linebot_t const self, linebot_mode_t mode);

static bool
is_tracking_route(linebot_t const self);

static uint16_t
validate_commands(uint16_t commands);

void
linebot_init(void)
{
    linebot_port_mode_init();
    linebot_port_coords_init();
    linebot_port_motion_init();
    linebot_port_control_init();

    memset(&pool, 0, sizeof(pool));

    position_init();
    motion_init();
    coords_init();
}

bool
linebot_new_coords(uint8_t const            l3,
                   uint8_t const            l2,
                   uint8_t const            l1,
                   uint8_t const            r1,
                   uint8_t const            r2,
                   uint8_t const            r3,
                   linebot_coords_t * const handle)
{
    return coords_new(l3, l2, l1, r1, r2, r3, handle);
}

bool
linebot_new(linebot_mode_t    mode,
            linebot_coords_t  coords,
            uint8_t           errsize,
            linebot_t * const handle)
{
    bool       linebot_created = false;
    position_t position;
    bool       position_created = position_new(coords, errsize, &position);

    if (linebot_pool_alloc(&pool, handle) && position_created)
    {
        linebot_instance_t *instance = linebot_pool_get(&pool, *handle);
        instance->mode               = mode;
        instance->position           = position;
        linebot_created              = true;
    }

    return linebot_created;
}

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result         = LINEBOT_OK;
    uint16_t         valid_commands = validate_commands(commands);
    bool             is_break       = valid_commands & LINEBOT_COMMAND_BREAK;

    if (!is_tracking_route(self) || is_break)
    {
        linebot_motion_t motion;

        if (motion_create_by_commands(valid_commands, &motion))
        {
            linebot_port_motion_apply(motion);
            motion_release(motion);
        }
    }

    return result;
}

linebot_result_t
linebot_change_mode_by_control(linebot_t const self, uint16_t const commands)
{
    linebot_instance_t *linebot = linebot_pool_get(&pool, self);
    linebot_mode_t      mode = mode_change_by_commands(linebot->mode, commands);

    if (set_mode(self, mode) == LINEBOT_MODE_CHANGED)
    {
        linebot_port_mode_changed(mode);
    }

    return LINEBOT_OK;
}

linebot_result_t
linebot_apply_following_motion(linebot_t const        self,
                               linebot_coords_t const coords)
{
    linebot_result_t result = LINEBOT_OK;

    if (is_tracking_route(self) || coords_is_on_finish(coords))
    {
        linebot_instance_t *linebot = linebot_pool_get(&pool, self);
        linebot_motion_t    motion;

        position_update_coords(linebot->position, coords);

        if (motion_create_by_position(linebot->position, &motion))
        {
            linebot_port_motion_apply(motion);
            motion_release(motion);
        }
    }

    return result;
}

linebot_result_t
linebot_change_mode_by_coords(linebot_t const        self,
                              linebot_coords_t const coords)
{
    linebot_instance_t *linebot  = linebot_pool_get(&pool, self);
    linebot_mode_t      new_mode = mode_change_by_coords(linebot->mode, coords);

    if (set_mode(self, new_mode) == LINEBOT_MODE_CHANGED)
    {
        linebot_port_mode_changed(new_mode);
    }

    return LINEBOT_OK;
}

linebot_result_t
linebot_timeout_route_guard(linebot_t const self)
{
    linebot_motion_t motion;
    linebot_result_t result = motion_create_standby(&motion);

    if (result == LINEBOT_OK)
    {
        linebot_mode_t new_mode = LINEBOT_MODE_MANUAL;
        set_mode(self, new_mode);
        linebot_port_mode_changed(new_mode);
        linebot_port_motion_apply(motion);
        motion_release(motion);
    }

    return result;
}

linebot_mode_t
linebot_get_mode(linebot_t const self)
{
    linebot_instance_t *linebot = linebot_pool_get(&pool, self);
    return linebot->mode;
}

linebot_motion_direction_t
linebot_get_motion_direction(linebot_motion_t const self)
{
    return motion_get_direction(self);
}

int8_t
linebot_get_motion_correction(linebot_motion_t const self)
{
    return motion_get_correction(self);
}

static linebot_result_t
set_mode(linebot_t const self, linebot_mode_t mode)
{
    linebot_result_t    result  = LINEBOT_OK;
    linebot_instance_t *linebot = linebot_pool_get(&pool, self);

    if (linebot->mode != mode)
    {
        linebot->mode = mode;
        result        = LINEBOT_MODE_CHANGED;
    }

    return result;
}

static bool
is_tracking_route(linebot_t const self)
{
    return linebot_get_mode(self) == LINEBOT_MODE_FOLLOWING ||
           linebot_get_mode(self) == LINEBOT_MODE_RECOVERING;
}

static uint16_t
validate_commands(uint16_t commands)
{
    uint16_t filtered     = commands;
    bool     has_forward  = commands & LINEBOT_MOTION_FORWARD;
    bool     has_backward = commands & LINEBOT_MOTION_BACKWARD;
    bool     has_left     = commands & LINEBOT_COMMAND_LEFT;
    bool     has_right    = commands & LINEBOT_COMMAND_RIGHT;

    if (has_forward && has_backward)
    {
        filtered = LINEBOT_COMMAND_NONE;
    }

    if ((has_left || has_right) && !(has_forward || has_backward))
    {
        filtered = LINEBOT_COMMAND_NONE;
    }

    if (has_right && has_left)
    {
        filtered = LINEBOT_COMMAND_NONE;
    }

    return filtered;
}