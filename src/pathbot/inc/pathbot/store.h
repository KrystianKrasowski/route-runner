#ifndef _PATHBOT_STORE_H
#define _PATHBOT_STORE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <pathbot/domain.h>
#include <utils/stack.h>

typedef struct
{
    pathbot_mode_t     mode;
    stack_t            past_errors;
    pathbot_pid_conf_t pid_conf;
    pathbot_motion_t   motion;
} pathbot_store_t;

void
pathbot_store_init(pathbot_store_t const * const p_self);

pathbot_store_t *
pathbot_store_get(void);

#ifdef __cplusplus
}
#endif

#endif
