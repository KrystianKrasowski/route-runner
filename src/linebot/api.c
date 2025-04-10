#include "command.h"
#include "coords.h"
#include "linebot.h"
#include "mode.h"
#include "motion_factory.h"
#include "position.h"
#include <linebot/api.h>
#include <linebot/port.h>
#include <string.h>
#include <utils/pool.h>

void
linebot_init(void)
{
    linebot_port_mode_init();
    linebot_port_coords_init();
    linebot_port_motion_init();
    linebot_port_control_init();
}

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result = LINEBOT_OK;

    if (!linebot_is_tracking_route(self) || command_has_break(commands))
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
    linebot_mode_t mode     = linebot_get_mode(self);
    linebot_mode_t new_mode = mode_change_by_commands(mode, commands);

    if (linebot_update_mode(self, new_mode))
    {
        linebot_port_mode_changed(new_mode);
    }

    return LINEBOT_OK;
}

linebot_result_t
linebot_apply_tracking_motion(linebot_t const        self,
                              linebot_coords_t const coords)
{
    linebot_result_t result = LINEBOT_OK;

    if (linebot_is_tracking_route(self) || coords_is_on_finish(coords))
    {
        position_t       position = linebot_get_position(self);
        linebot_motion_t motion;

        position_update_coords(position, coords);

        if (motion_create_by_position(position, &motion))
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
    linebot_mode_t mode     = linebot_get_mode(self);
    linebot_mode_t new_mode = mode_change_by_coords(mode, coords);

    if (linebot_update_mode(self, new_mode))
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
        linebot_update_mode(self, new_mode);
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