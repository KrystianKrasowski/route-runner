#include "command.h"

bool
command_has_forward(uint16_t commands)
{
    return (commands & LINEBOT_COMMAND_FORWARD) &&
           !(commands & LINEBOT_COMMAND_BACKWARD);
}

bool
command_has_backward(uint16_t commands)
{
    return (commands & LINEBOT_COMMAND_BACKWARD) &&
           !(commands & LINEBOT_COMMAND_FORWARD);
}

bool
command_has_right(uint16_t commands)
{
    return (commands & LINEBOT_COMMAND_RIGHT) &&
           !(commands & LINEBOT_COMMAND_LEFT);
}

bool
command_has_left(uint16_t commands)
{
    return (commands & LINEBOT_COMMAND_LEFT) &&
           !(commands & LINEBOT_COMMAND_RIGHT);
}

bool
command_has_break(uint16_t commands)
{
    return commands & LINEBOT_COMMAND_BREAK;
}

bool
command_has_follow(uint16_t commands)
{
    return commands & LINEBOT_COMMAND_FOLLOW;
}

bool
command_has_move(uint16_t commands)
{
    return command_has_forward(commands) || command_has_backward(commands);
}