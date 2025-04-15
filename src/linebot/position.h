#ifndef _POSITION_H
#define _POSITION_H

#include <linebot/coords.h>
#include <stdint.h>

typedef uint8_t position_t;

void
position_init(void);

int
position_acquire(linebot_coords_t   coords,
                 uint8_t            errsize,
                 position_t * const ph_self);

void
position_release(position_t const h_self);

void
position_update_coords(position_t const       h_self,
                       linebot_coords_t const h_coords);

bool
position_is_on_finish(position_t const h_self);

int8_t
position_last_error(position_t const h_self);

int8_t
position_update_error(position_t const h_self);

int16_t
position_sum_errors(position_t const h_self);

int8_t
position_regulate(position_t const h_self);

#endif