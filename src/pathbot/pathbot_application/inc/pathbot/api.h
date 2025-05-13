#ifndef _PATHBOT_API_H
#define _PATHBOT_API_H

#include <pathbot/domain.h>
#include <stdint.h>

typedef enum
{
    PATHBOT_RESULT_OK = 0,
    PATHBOT_RESULT_NOOP,
} pathbot_result_t;

int
pathbot_handle_commands(uint16_t commands);

#endif
