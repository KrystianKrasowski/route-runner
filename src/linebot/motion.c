#include <linebot/motion.h>

linebot_direction_t
linebot_motion_invert_direction(linebot_motion_t const *p_self)
{
    switch (p_self->direction)
    {
        case LINEBOT_DIRECTION_FORWARD:
            return LINEBOT_DIRECTION_BACKWARD;

        case LINEBOT_DIRECTION_BACKWARD:
            return LINEBOT_DIRECTION_FORWARD;

        default:
            return LINEBOT_DIRECTION_NONE;
    }
}
