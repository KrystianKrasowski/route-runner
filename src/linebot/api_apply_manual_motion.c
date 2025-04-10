#include "command.h"
#include "linebot.h"
#include "motion_factory.h"
#include <linebot/api.h>
#include <linebot/port.h>

static inline linebot_result_t
create_and_apply_motion(uint16_t const commands);

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands)
{
    linebot_result_t result = LINEBOT_OK;

    if (!linebot_is_tracking_route(self) || command_has_break(commands))
    {
        result = create_and_apply_motion(commands);
    }

    return result;
}

static inline linebot_result_t
create_and_apply_motion(uint16_t const commands)
{
    linebot_result_t result = LINEBOT_OK;
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

    return result;
}