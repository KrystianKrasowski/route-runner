#ifndef _LINEBOT_H
#define _LINEBOT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    LINEBOT_COMMAND_NONE     = 0,
    LINEBOT_COMMAND_FORWARD  = 1,
    LINEBOT_COMMAND_BACKWARD = 2,
    LINEBOT_COMMAND_LEFT     = 4,
    LINEBOT_COMMAND_RIGHT    = 8,
    LINEBOT_COMMAND_BREAK    = 16,
    LINEBOT_COMMAND_FOLLOW   = 32,
} linebot_command_t;

typedef enum
{
    LINEBOT_MODE_MANUAL,
    LINEBOT_MODE_DETECTED,
    LINEBOT_MODE_FOLLOWING,
    LINEBOT_MODE_RECOVERING,
} linebot_mode_t;

typedef enum
{
    LINEBOT_OK,
    LINEBOT_ERROR,
    LINEBOT_OBJECT_POOL_ERROR,
    LINEBOT_MODE_CHANGED,
} linebot_result_t;

typedef enum
{
    LINEBOT_MOTION_NONE,
    LINEBOT_MOTION_FORWARD,
    LINEBOT_MOTION_BACKWARD,
} linebot_motion_direction_t;

// TODO: should provide some handle from generic pool util. With uint8_t one can
// provide different object's handle value!
typedef uint8_t linebot_t;
typedef uint8_t linebot_coords_t;
typedef uint8_t linebot_motion_t;

void
linebot_init(void);

bool
linebot_new_coords(uint8_t const            l3,
                   uint8_t const            l2,
                   uint8_t const            l1,
                   uint8_t const            r1,
                   uint8_t const            r2,
                   uint8_t const            r3,
                   linebot_coords_t * const handle);

bool
linebot_new(linebot_mode_t    mode,
            linebot_coords_t  coords,
            uint8_t           errors_size,
            linebot_t * const handle);

linebot_result_t
linebot_apply_manual_motion(linebot_t const self, uint16_t const commands);

linebot_result_t
linebot_change_mode_by_control(linebot_t const self, uint16_t const commands);

linebot_result_t
linebot_apply_following_motion(linebot_t const        self,
                               linebot_coords_t const coords);

linebot_result_t
linebot_change_mode_by_coords(linebot_t const        self,
                              linebot_coords_t const coords);

linebot_result_t
linebot_timeout_route_guard(linebot_t const self);

linebot_mode_t
linebot_get_mode(linebot_t const self);

linebot_motion_direction_t
linebot_get_motion_direction(linebot_motion_t const self);

int8_t
linebot_get_motion_correction(linebot_motion_t const self);

void
linebot_port_control_init(void);

uint16_t
linebot_port_control_command_map(uint16_t const raw_command);

void
linebot_port_coords_init(void);

linebot_coords_t
linebot_port_coords_map(uint8_t *raw);

void
linebot_port_motion_init(void);

void
linebot_port_motion_apply(linebot_motion_t const motion);

void
linebot_port_mode_init(void);

void
linebot_port_mode_changed(linebot_mode_t const value);

#endif