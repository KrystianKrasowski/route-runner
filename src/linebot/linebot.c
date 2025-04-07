#include "coords.h"
#include "mode.h"
#include "motion.h"
#include "motion_factory.h"
#include "position.h"
#include <linebot.h>
#include <string.h>

#define LINEBOT_POOL_SIZE 1

typedef struct
{
    linebot_mode_t mode;
    position_t     position;
} linebot_instance_t;

typedef struct
{
    linebot_instance_t instances[LINEBOT_POOL_SIZE];
    bool               in_use[LINEBOT_POOL_SIZE];
} linebot_pool_t;

static linebot_pool_t pool;

static inline void
init_pool(void);

static inline void
init_ports(void);

static linebot_result_t
linebot_set_mode(linebot_t const self, linebot_mode_t mode);

void
linebot_init(void)
{
    init_ports();
    init_pool();
    position_init();
    motion_init();
    coords_init();
}

linebot_result_t
linebot_new_instance(linebot_t * const handle)
{
    linebot_result_t result;
    uint8_t          index = LINEBOT_POOL_SIZE;
    position_t       position;

    for (uint8_t i = 0; i < LINEBOT_POOL_SIZE; i++)
    {
        if (false == pool.in_use[i])
        {
            index = i;
            break;
        }
    }

    bool pool_full        = index == LINEBOT_POOL_SIZE;
    bool position_created = position_new_instance(&position) == LINEBOT_SUCCESS;

    if (!pool_full && position_created)
    {
        pool.in_use[index]             = true;
        pool.instances[index].mode     = LINEBOT_MODE_MANUAL;
        pool.instances[index].position = position;
        *handle                        = index;
        result                         = LINEBOT_SUCCESS;
    }
    else
    {
        result = LINEBOT_ERROR;
    }

    return result;
}

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result      = LINEBOT_SUCCESS;
    bool             is_tracking = linebot_is_tracking_route(self);
    bool             is_break    = commands & LINEBOT_COMMAND_BREAK;

    if (!is_tracking || is_break)
    {
        linebot_motion_t motion;
        result = motion_create_by_commands(commands, &motion);

        if (result == LINEBOT_SUCCESS)
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
    linebot_mode_t current_mode = pool.instances[self].mode;
    linebot_mode_t new_mode = mode_change_by_commands(current_mode, commands);

    if (linebot_set_mode(self, new_mode) == LINEBOT_MODE_CHANGED)
    {
        linebot_port_mode_changed(new_mode);
    }

    return LINEBOT_SUCCESS;
}

linebot_result_t
linebot_apply_following_motion(linebot_t const        self,
                               linebot_coords_t const coords)
{
    linebot_result_t result = LINEBOT_SUCCESS;

    if (linebot_is_tracking_route(self) || coords_is_on_finish(coords))
    {
        linebot_motion_t motion;
        position_t       position = pool.instances[self].position;

        position_update_coords(position, coords);
        result = motion_create_by_position(position, &motion);

        if (result == LINEBOT_SUCCESS)
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
    linebot_mode_t current_mode = pool.instances[self].mode;
    linebot_mode_t new_mode     = mode_change_by_coords(current_mode, coords);

    if (linebot_set_mode(self, new_mode) == LINEBOT_MODE_CHANGED)
    {
        linebot_port_mode_changed(new_mode);
    }

    return LINEBOT_SUCCESS;
}

linebot_result_t
linebot_timeout_route_guard(linebot_t const self)
{
    linebot_motion_t motion;
    linebot_result_t result = motion_create_standby(&motion);

    if (result == LINEBOT_SUCCESS)
    {
        linebot_mode_t new_mode = LINEBOT_MODE_MANUAL;
        linebot_set_mode(self, new_mode);
        linebot_port_mode_changed(new_mode);
        linebot_port_motion_apply(motion);
        motion_release(motion);
    }

    return result;
}

bool
linebot_is_remote_controlled(linebot_t const self)
{
    return mode_is_manual(pool.instances[self].mode);
}

bool
linebot_is_route_detected(linebot_t const self)
{
    return mode_is_route_detected(pool.instances[self].mode);
}

bool
linebot_is_tracking_route(linebot_t const self)
{
    return mode_is_tracking_route(pool.instances[self].mode);
}

bool
linebot_is_following_route(linebot_t const self)
{
    return mode_is_following_route(pool.instances[self].mode);
}

bool
linebot_is_recovering_route(linebot_t const self)
{
    return mode_is_recovering_route(pool.instances[self].mode);
}

static inline void
init_ports(void)
{
    linebot_port_mode_init();
    linebot_port_coords_init();
    linebot_port_motion_init();
    linebot_port_control_init();
}

static inline void
init_pool(void)
{
    memset(&pool, 0, sizeof(pool));
}

static linebot_result_t
linebot_set_mode(linebot_t const self, linebot_mode_t mode)
{
    if (pool.instances[self].mode == mode)
    {
        return LINEBOT_SUCCESS;
    }
    else
    {
        pool.instances[self].mode = mode;
        return LINEBOT_MODE_CHANGED;
    }
}