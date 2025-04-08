#ifndef _LINEBOT_POSITION_H
#define _LINEBOT_POSITION_H

#include <linebot.h>
#include <stdint.h>

typedef uint8_t position_t;

void
position_init(void);

bool
position_new(linebot_coords_t   coords,
             uint8_t            errsize,
             position_t * const handle);

void
position_update_coords(position_t const self, linebot_coords_t const coords);

bool
position_is_on_finish(position_t const self);

int8_t
position_last_error(position_t const self);

int8_t
position_update_error(position_t const self);

int16_t
position_sum_errors(position_t const self);

int8_t
position_regulate(position_t const self);

#endif