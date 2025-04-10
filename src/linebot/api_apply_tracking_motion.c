#include "command.h"
#include "coords.h"
#include "linebot.h"
#include "motion_factory.h"
#include <linebot/api.h>
#include <linebot/port.h>

static inline linebot_result_t
update_position_coordinates(linebot_t const        self,
                            linebot_coords_t const coords,
                            position_t * const     position);

static inline linebot_result_t
create_and_apply_motion(linebot_coords_t const coords);

linebot_result_t
linebot_apply_tracking_motion(linebot_t const        self,
                              linebot_coords_t const coords)
{
    linebot_result_t result = LINEBOT_OK;

    if (linebot_is_tracking_route(self) || coords_is_on_finish(coords))
    {
        position_t position;
        result = update_position_coordinates(self, coords, &position);
        result = create_and_apply_motion(position);
    }

    return result;
}

static inline linebot_result_t
update_position_coordinates(linebot_t const        self,
                            linebot_coords_t const coords,
                            position_t * const     position)
{
    linebot_result_t result = linebot_get_position(self, position);

    if (LINEBOT_OK == result)
    {
        position_update_coords(*position, coords);
    }

    return result;
}

static inline linebot_result_t
create_and_apply_motion(position_t const position)
{
    linebot_result_t result = LINEBOT_OK;
    linebot_motion_t motion;

    if (motion_create_by_position(position, &motion))
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