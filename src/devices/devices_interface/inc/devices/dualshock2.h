#ifndef _DEVICES_DUALSHOCK2_H
#define _DEVICES_DUALSHOCK2_H

#include <stdint.h>

typedef enum
{
    DS2_NONE     = 0,
    DS2_SELECT   = 1,
    DS2_L3       = 2,
    DS2_R3       = 4,
    DS2_START    = 8,
    DS2_UP       = 16,
    DS2_RIGHT    = 32,
    DS2_DOWN     = 64,
    DS2_LEFT     = 128,
    DS2_L2       = 256,
    DS2_R2       = 512,
    DS2_L1       = 1024,
    DS2_R1       = 2048,
    DS2_TRIANGLE = 4096,
    DS2_CIRCLE   = 8192,
    DS2_CROSS    = 16384,
    DS2_SQUARE   = 32768,
} dualshock2_command_t;

typedef enum
{
    DEVICES_DUALSHOCK2_1,
} dualshock2_t;

int
devices_dualshock2_read(dualshock2_t h_self, uint16_t *p_commands);

#endif