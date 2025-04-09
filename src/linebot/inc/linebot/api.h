#ifndef _LINEBOT_API_H
#define _LINEBOT_API_H

#include "command.h"
#include "coords.h"
#include "mode.h"
#include "motion.h"

typedef enum
{
    LINEBOT_OK,
    LINEBOT_ERROR_OBJECT_POOL,
} linebot_result_t;

typedef uint8_t linebot_t;

void
linebot_init(void);

bool
linebot_new(linebot_mode_t    mode,
            linebot_coords_t  coords,
            uint8_t           errors_size,
            linebot_t * const handle);

void
linebot_free(linebot_t linebot);

linebot_mode_t
linebot_get_mode(linebot_t const self);

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
linebot_stop(linebot_t const self);

#endif