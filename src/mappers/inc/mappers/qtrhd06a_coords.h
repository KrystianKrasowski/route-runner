#ifndef _QTRHD06A_COORDS_H
#define _QTRHD06A_COORDS_H

#include <pathbot/domain.h>
#include <stdint.h>

void
mapper_qtrhd06a_coords_read(uint8_t                  raw_values[],
                            uint8_t const            raw_values_size,
                            pathbot_coords_t * const p_coords);

#endif
