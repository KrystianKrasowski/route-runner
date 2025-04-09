#ifndef _COMMAND_H
#define _COMMAND_H

#include <linebot/command.h>
#include <stdbool.h>
#include <stdint.h>

bool
command_has_forward(uint16_t commands);

bool
command_has_backward(uint16_t commands);

bool
command_has_right(uint16_t commands);

bool
command_has_left(uint16_t commands);

bool
command_has_break(uint16_t commands);

bool
command_has_follow(uint16_t commands);

bool
command_has_move(uint16_t commands);

#endif