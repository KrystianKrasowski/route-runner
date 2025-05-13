#ifndef _PATHBOT_STORE_H
#define _PATHBOT_STORE_H

#include <pathbot/domain.h>

typedef struct
{
    uint16_t         commands;
    pathbot_mode_t   mode;
    pathbot_motion_t motion;
} pathbot_store_t;

pathbot_store_t *
pathbot_store_get(void);

#endif
