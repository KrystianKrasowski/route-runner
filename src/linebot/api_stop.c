#include "linebot.h"
#include "mode.h"
#include "motion_factory.h"
#include <linebot/api.h>
#include <linebot/port.h>
#include <utils/pool.h>

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
        linebot_motion_release(motion);
    }
    else
    {
        result = LINEBOT_ERR_POOL_EXCEEDED;
    }

    return result;
}