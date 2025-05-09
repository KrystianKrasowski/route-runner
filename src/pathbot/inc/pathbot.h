#ifndef _PATHBOT_H
#define _PATHBOT_H

#include <stdint.h>

typedef enum
{
    PATHBOT_COMMAND_NONE     = 0,
    PATHBOT_COMMAND_FORWARD  = 1,
    PATHBOT_COMMAND_BACKWARD = 2,
    PATHBOT_COMMAND_LEFT     = 4,
    PATHBOT_COMMAND_RIGHT    = 8,
    PATHBOT_COMMAND_BREAK    = 16,
    PATHBOT_COMMAND_FOLLOW   = 32,
} pathbot_command_t;

typedef enum
{
    PATHBOT_MODE_MANUAL,
    PATHBOT_MODE_DETECTED,
    PATHBOT_MODE_FOLLOWING,
    PATHBOT_MODE_RECOVERING,
} pathbot_mode_t;

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t current, uint16_t commands);

#endif
