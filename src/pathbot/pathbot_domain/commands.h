#ifndef _PATHBOT_COMMANDS_H
#define _PATHBOT_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

bool
commands_has_forward(uint16_t const commands);

bool
commands_has_backward(uint16_t const commands);

bool
commands_has_right(uint16_t const commands);

bool
commands_has_left(uint16_t const commands);

bool
commands_has_move(uint16_t const commands);

bool
commands_has_break(uint16_t const commands);

bool
commands_has_follow(uint16_t const commands);

#endif
