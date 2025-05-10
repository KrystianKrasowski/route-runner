#ifndef _PATHBOT_H
#define _PATHBOT_H

#include <stdint.h>

#define PATHBOT_MAX_COORDS_LENGTH 6
#define PATHBOT_COORDS_WEIGHTS_6  {-100, -40, -10, 10, 40, 100}

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
    pathbot_direction_t const direction;
    int8_t const              correction;
} pathbot_motion_t;

typedef struct
{
    uint8_t const coords[PATHBOT_MAX_COORDS_LENGTH];
    uint8_t const weights[PATHBOT_MAX_COORDS_LENGTH];
    uint8_t const length;
} pathbot_coords_t;

pathbot_mode_t
pathbot_update_mode_manual(pathbot_mode_t const current_mode,
                           uint16_t const       commands);

pathbot_mode_t
pathbot_update_mode_tracking(pathbot_mode_t const    current_mode,
                             pathbot_coords_t const *p_coords);

pathbot_motion_t
pathbot_create_motion_manual(pathbot_mode_t const current_mode,
                             uint16_t const       commands);

#endif
