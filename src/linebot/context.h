#ifndef _API_CONTEXT_H
#define _API_CONTEXT_H

#include "position.h"
#include <linebot/api.h>

void
context_init(void);

int
context_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle);

int
context_validate(linebot_t const self);

void
context_release(linebot_t const self);

linebot_mode_t
context_get_mode(linebot_t const self);

position_t
context_get_position(linebot_t const self);

bool
context_update_mode(linebot_t const self, linebot_mode_t mode);

bool
context_is_tracking_route(linebot_t const self);

#endif