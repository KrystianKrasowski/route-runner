#include <pathbot/store.h>
#include <stddef.h>

static pathbot_store_t store;

void
pathbot_store_init(pathbot_store_t const * const p_self)
{
    if (NULL == p_self)
    {
        store.commands    = PATHBOT_COMMAND_NONE;
        store.mode        = PATHBOT_MODE_MANUAL;
        store.past_errors = stack(20);
        store.pid_conf.kp = 0.6;
        store.pid_conf.ki = 0;
        store.pid_conf.kd = 3.2;
    }
    else
    {
        store = *p_self;
    }
}

pathbot_store_t *
pathbot_store_get(void)
{
    return &store;
}
