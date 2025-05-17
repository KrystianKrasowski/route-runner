#include "mode.h"
#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>
#include <stdint.h>

static inline void
handle_mode_transition(uint16_t commands, pathbot_store_t * const p_store);

static inline void
handle_motion_apply(uint16_t commands, pathbot_store_t * const p_store);

void
pathbot_handle_commands(uint16_t const commands)
{
    pathbot_store_t * const p_store = pathbot_store_get();

    handle_motion_apply(commands, p_store);
    handle_mode_transition(commands, p_store);
}

static inline void
handle_mode_transition(uint16_t commands, pathbot_store_t * const p_store)
{
    if (mode_update_manual(commands, &p_store->mode))
    {
        pathbot_port_mode_changed(p_store->mode);
    }
}

static inline void
handle_motion_apply(uint16_t commands, pathbot_store_t * const p_store)
{
    if (!pathbot_mode_is_tracking(p_store->mode) &&
        motion_update_manual(commands, &p_store->motion))
    {
        pathbot_port_motion_apply(&p_store->motion);
    }
}
