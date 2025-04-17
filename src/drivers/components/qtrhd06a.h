#ifndef _QTRHD06A_H
#define _QTRHD06A_H

#include <stdint.h>

void
qtrhd06a_init(void);

void
qtrhd06a_parse_values(uint8_t const *byte_buffer, uint8_t *p_values);

#endif