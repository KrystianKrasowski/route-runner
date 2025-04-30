#include "command.h"
#include "linebot/motion.h"
#include "motion_factory.h"
#include "position.h"

static inline linebot_direction_t
create_manual_direction(uint16_t const commands);

static inline int8_t
create_manual_correction(uint16_t const commands);

linebot_motion_t
motion_create_by_commands(uint16_t const commands)
{
    return (linebot_motion_t){
        .correction = create_manual_correction(commands),
        .direction  = create_manual_direction(commands),
    };
}

linebot_motion_t
motion_create_by_position(position_t const h_position)
{
    if (position_is_on_finish(h_position))
    {
        return (linebot_motion_t){
            .correction = 0,
            .direction  = LINEBOT_DIRECTION_NONE,
        };
    }
    else
    {
        return (linebot_motion_t){
            .correction = position_regulate(h_position),
            .direction  = LINEBOT_DIRECTION_FORWARD,
        };
    }
}

linebot_motion_t
motion_create_standby(void)
{
    return (linebot_motion_t){
        .correction = 0,
        .direction  = LINEBOT_DIRECTION_NONE,
    };
}

static inline linebot_direction_t
create_manual_direction(uint16_t const commands)
{
    linebot_direction_t direction;

    if (command_has_forward(commands))
    {
        direction = LINEBOT_DIRECTION_FORWARD;
    }
    else if (command_has_backward(commands))
    {
        direction = LINEBOT_DIRECTION_BACKWARD;
    }
    else
    {
        direction = LINEBOT_DIRECTION_NONE;
    }

    return direction;
}

static inline int8_t
create_manual_correction(uint16_t const commands)
{
    int8_t correction;

    if (command_has_left(commands) && command_has_move(commands))
    {
        correction = -50;
    }
    else if (command_has_right(commands) && command_has_move(commands))
    {
        correction = 50;
    }
    else
    {
        correction = 0;
    }

    return correction;
}
