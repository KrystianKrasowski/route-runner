#include "mode.h"
#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>
#include <stdint.h>

static inline void
handle_mode_transition(pathbot_store_t * const p_store);

static inline void
handle_motion_apply(pathbot_store_t * const p_store);

int
pathbot_handle_commands(uint16_t const commands)
{
    pathbot_store_t * const p_store = pathbot_store_get();

    if (commands == p_store->commands)
    {
        return PATHBOT_RESULT_NOOP;
    }

    p_store->commands = commands;

    handle_mode_transition(p_store);
    handle_motion_apply(p_store);

    return PATHBOT_RESULT_OK;
}

static inline void
handle_mode_transition(pathbot_store_t * const p_store)
{
    if (mode_update_manual(p_store->commands, &p_store->mode))
    {
        pathbot_port_mode_changed(p_store->mode);
    }
}

static inline void
handle_motion_apply(pathbot_store_t * const p_store)
{
    if (!mode_is_tracking(p_store->mode) &&
        motion_update_manual(p_store->commands, &p_store->motion))
    {
        pathbot_port_motion_apply(&p_store->motion);
    }
}
