#ifndef _MAPPERS_DUALSHOCK_CONTROL_H
#define _MAPPERS_DUALSHOCK_CONTROL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

uint16_t
mapper_dualshock2_control_read(uint16_t const dualshock2_state);

#ifdef __cplusplus
}
#endif

#endif
