#ifndef _API_CONTEXT_H
#define _API_CONTEXT_H

#include "position.h"
#include <linebot/api.h>

void
context_init(void);

int
context_acquire(linebot_mode_t    mode,
                linebot_coords_t  h_coords,
                uint8_t           errsize,
                linebot_t * const ph_self);

int
context_validate(linebot_t const h_self);

void
context_release(linebot_t const h_self);

linebot_mode_t
context_get_mode(linebot_t const h_self);

position_t
context_get_position(linebot_t const h_self);

bool
context_update_mode(linebot_t const h_self, linebot_mode_t const mode);

bool
context_is_tracking_route(linebot_t const h_self);

#endif