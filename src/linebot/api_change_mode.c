#include "command.h"
#include "linebot.h"
#include "mode.h"
#include <linebot/api.h>
#include <linebot/port.h>

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