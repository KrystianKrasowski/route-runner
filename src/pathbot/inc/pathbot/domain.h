#ifndef _PATHBOT_H
#define _PATHBOT_H

#include <stdint.h>
#include <utils/stack.h>

#define PATHBOT_MAX_COORDS_LENGTH 6
#define PATHBOT_COORDS6_WEIGHTS   {-100, -40, -20, 20, 40, 100}

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
    PATHBOT_MODE_MANUAL = 0,
    PATHBOT_MODE_DETECTED,
    PATHBOT_MODE_FOLLOWING,
    PATHBOT_MODE_RECOVERING,
} pathbot_mode_t;

typedef enum
{
    PATHBOT_DIRECTION_NONE = 0,
    PATHBOT_DIRECTION_FORWARD,
    PATHBOT_DIRECTION_BACKWARD,
} pathbot_direction_t;

typedef struct
{
    pathbot_direction_t direction;
    int8_t              correction;
} pathbot_motion_t;

typedef struct
{
    uint8_t coords[PATHBOT_MAX_COORDS_LENGTH];
    int8_t  weights[PATHBOT_MAX_COORDS_LENGTH];
    uint8_t length;
} pathbot_coords_t;

typedef struct
{
    float kp;
    float ki;
    float kd;
} pathbot_pid_conf_t;

#endif
