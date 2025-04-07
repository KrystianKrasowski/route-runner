#ifndef _LINEBOT_POSITION_H
#define _LINEBOT_POSITION_H

#include <linebot.h>
#include <stdint.h>

typedef uint8_t position_t;

void
position_init(void);

linebot_result_t
position_new_instance(position_t * const handle);

void
position_update_coords(position_t const self, linebot_coords_t const coords);

int8_t
position_last_error(position_t const self);

int8_t
position_update_error(position_t const self);

int16_t
position_sum_errors(position_t const self);

int8_t
position_regulate(position_t const self);

#endif