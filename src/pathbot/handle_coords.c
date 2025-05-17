#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>
#include <stdint.h>

int
pathbot_handle_coords(pathbot_coords_t const * const p_coords)
{
    pathbot_store_t *p_store = pathbot_store_get();

    if (mode_update_tracking(p_coords, &p_store->mode))
    {
        pathbot_port_mode_changed(p_store->mode);
    }

    if (pathbot_mode_is_tracking(p_store->mode))
    {
        int8_t error = coords_compute_mass_center(p_coords);

        if (motion_update_pid(error,
                              &p_store->past_errors,
                              &p_store->pid_conf,
                              &p_store->motion))
        {
            pathbot_port_motion_apply(&p_store->motion);
        }

        stack_push_rolling(&p_store->past_errors, error);
    }

    return PATHBOT_RESULT_OK;
}
