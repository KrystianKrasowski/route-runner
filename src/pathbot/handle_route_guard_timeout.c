#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>

void
pathbot_handle_route_guard_timeout(void)
{
    pathbot_store_t *p_store = pathbot_store_get();

    p_store->mode = PATHBOT_MODE_MANUAL;
    motion_stop(&p_store->motion);

    pathbot_port_motion_apply(&p_store->motion);
    pathbot_port_mode_changed(p_store->mode);
}
