#include "command.h"
#include "coords.h"
#include "mode.h"
#include "motion_factory.h"
#include "position.h"
#include <linebot/api.h>
#include <linebot/port.h>
#include <string.h>
#include <utils/pool.h>

typedef struct
{
    linebot_mode_t mode;
    position_t     position;
} linebot_instance_t;

POOL_DECLARE(linebot, linebot_instance_t, 1)

static linebot_pool_t pool;
static bool           pool_initialized = false;

static bool
set_mode(linebot_t const self, linebot_mode_t mode);

static inline bool
is_tracking_route(linebot_t const self);

void
linebot_init(void)
{
    linebot_port_mode_init();
    linebot_port_coords_init();
    linebot_port_motion_init();
    linebot_port_control_init();
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

    if (!pool_initialized)
    {
        pool_initialized = true;
        linebot_pool_init(&pool);
    }

    if (linebot_pool_alloc(&pool, handle) && position_created)
    {
        linebot_instance_t *instance = linebot_pool_get(&pool, *handle);
        instance->mode               = mode;
        instance->position           = position;
        linebot_created              = true;
    }

    return linebot_created;
}

void
// cppcheck-suppress unusedFunction
linebot_free(linebot_t self)
{
    linebot_instance_t const *linebot = linebot_pool_get(&pool, self);

    position_free(linebot->position);
    linebot_pool_free(&pool, self);
}

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result = LINEBOT_OK;

    if (!is_tracking_route(self) || command_has_break(commands))
    {
        linebot_motion_t motion;

        if (motion_create_by_commands(commands, &motion))
        {
            linebot_port_motion_apply(motion);
            linebot_motion_free(motion);
        }
        else
        {
            result = LINEBOT_ERROR_OBJECT_POOL;
        }
    }

    return result;
}

linebot_result_t
linebot_change_mode_by_control(linebot_t const self, uint16_t const commands)
{
    linebot_instance_t *linebot = linebot_pool_get(&pool, self);
    linebot_mode_t      mode = mode_change_by_commands(linebot->mode, commands);

    if (set_mode(self, mode))
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
        linebot_instance_t const *linebot = linebot_pool_get(&pool, self);
        linebot_motion_t    motion;

        position_update_coords(linebot->position, coords);

        if (motion_create_by_position(linebot->position, &motion))
        {
            linebot_port_motion_apply(motion);
            linebot_motion_free(motion);
        }
        else
        {
            result = LINEBOT_ERROR_OBJECT_POOL;
        }
    }

    return result;
}

linebot_result_t
linebot_change_mode_by_coords(linebot_t const        self,
                              linebot_coords_t const coords)
{
    linebot_instance_t const *linebot  = linebot_pool_get(&pool, self);
    linebot_mode_t      new_mode = mode_change_by_coords(linebot->mode, coords);

    if (set_mode(self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }

    return LINEBOT_OK;
}

linebot_result_t
linebot_stop(linebot_t const self)
{
    linebot_motion_t motion;
    linebot_result_t result = LINEBOT_OK;

    if (motion_create_standby(&motion))
    {
        linebot_mode_t new_mode = LINEBOT_MODE_MANUAL;
        set_mode(self, new_mode);
        linebot_port_mode_changed(new_mode);
        linebot_port_motion_apply(motion);
        linebot_motion_free(motion);
    }
    else
    {
        result = LINEBOT_ERROR_OBJECT_POOL;
    }

    return result;
}

linebot_mode_t
// cppcheck-suppress staticFunction
linebot_get_mode(linebot_t const self)
{
    linebot_instance_t const *linebot = linebot_pool_get(&pool, self);
    return linebot->mode;
}

static bool
set_mode(linebot_t const self, linebot_mode_t mode)
{
    bool                result  = false;
    linebot_instance_t *linebot = linebot_pool_get(&pool, self);

    if (linebot->mode != mode)
    {
        linebot->mode = mode;
        result        = true;
    }

    return result;
}

static inline bool
is_tracking_route(linebot_t const self)
{
    linebot_mode_t mode = linebot_get_mode(self);
    return linebot_mode_is_tracking(mode);
}