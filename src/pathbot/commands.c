#include "commands.h"
#include <pathbot.h>

bool
commands_has_forward(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_FORWARD &&
           !(commands & PATHBOT_COMMAND_BACKWARD);
}

bool
commands_has_backward(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_BACKWARD &&
           !(commands & PATHBOT_COMMAND_FORWARD);
}

bool
commands_has_right(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_RIGHT &&
           !(commands & PATHBOT_COMMAND_LEFT);
}

bool
commands_has_left(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_LEFT &&
           !(commands & PATHBOT_COMMAND_RIGHT);
}

bool
commands_has_move(uint16_t const commands)
{
    return commands_has_forward(commands) || commands_has_backward(commands);
}

bool
commands_has_break(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_BREAK;
}

bool
commands_has_follow(uint16_t const commands)
{
    return commands & PATHBOT_COMMAND_FOLLOW;
}
