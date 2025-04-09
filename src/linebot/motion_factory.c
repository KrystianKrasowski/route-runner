#include "motion_factory.h"
#include <linebot/command.h>

static inline linebot_motion_direction_t
create_manual_direction(uint16_t const commands);

static inline int8_t
create_manual_correction(uint16_t const commands);

bool
motion_create_by_commands(uint16_t const           commands,
                          linebot_motion_t * const handle)
{
    linebot_motion_direction_t direction  = create_manual_direction(commands);
    int8_t                     correction = create_manual_correction(commands);

    return linebot_motion_new(direction, correction, handle);
}

bool
motion_create_by_position(position_t const         position,
                          linebot_motion_t * const handle)
{
    bool result = false;

    if (position_is_on_finish(position))
    {
        result = linebot_motion_new(LINEBOT_MOTION_NONE, 0, handle);
    }
    else
    {
        int8_t correction = position_regulate(position);
        result = linebot_motion_new(LINEBOT_MOTION_FORWARD, correction, handle);
    }

    return result;
}

bool
motion_create_standby(linebot_motion_t * const handle)
{
    return linebot_motion_new(LINEBOT_MOTION_NONE, 0, handle);
}

static inline linebot_motion_direction_t
create_manual_direction(uint16_t const commands)
{
    linebot_motion_direction_t direction;

    if (commands & LINEBOT_COMMAND_FORWARD)
    {
        direction = LINEBOT_MOTION_FORWARD;
    }
    else if (commands & LINEBOT_COMMAND_BACKWARD)
    {
        direction = LINEBOT_MOTION_BACKWARD;
    }
    else
    {
        direction = LINEBOT_MOTION_NONE;
    }

    return direction;
}

static inline int8_t
create_manual_correction(uint16_t const commands)
{
    int8_t correction;

    if (commands & LINEBOT_COMMAND_LEFT)
    {
        correction = -50;
    }
    else if (commands & LINEBOT_COMMAND_RIGHT)
    {
        correction = 50;
    }
    else
    {
        correction = 0;
    }

    return correction;
}