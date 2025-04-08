#include "motion_factory.h"

static inline linebot_motion_direction_t
create_manual_direction(uint16_t const commands);

static inline int8_t
create_manual_correction(uint16_t const commands);

linebot_result_t
motion_create_by_commands(uint16_t const           commands,
                          linebot_motion_t * const handle)
{
    linebot_result_t result = motion_new_instance(handle);

    if (result == LINEBOT_OK)
    {
        motion_set_direction(*handle, create_manual_direction(commands));
        motion_set_correction(*handle, create_manual_correction(commands));
    }

    return result;
}

linebot_result_t
motion_create_by_position(position_t const         position,
                          linebot_motion_t * const handle)
{
    linebot_result_t result = motion_new_instance(handle);

    if (result == LINEBOT_OK)
    {
        int8_t correction = position_regulate(position);
        motion_set_direction(*handle, LINEBOT_MOTION_FORWARD);
        motion_set_correction(*handle, correction);
    }

    return result;
}

linebot_result_t
motion_create_standby(linebot_motion_t * const handle)
{
    linebot_result_t result = motion_new_instance(handle);

    if (result == LINEBOT_OK)
    {
        motion_set_direction(*handle, LINEBOT_MOTION_NONE);
        motion_set_correction(*handle, 0);
    }

    return result;
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