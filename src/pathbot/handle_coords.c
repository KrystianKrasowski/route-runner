#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>
#include <stdint.h>

static inline void
handle_pid_motion(pathbot_coords_t const * const p_coords,
                  pathbot_store_t * const        p_store);

int
pathbot_handle_coords(pathbot_coords_t const * const p_coords)
{
    pathbot_store_t *p_store = pathbot_store_get();

    if (mode_update_tracking(p_coords, &p_store->mode))
    {
        pathbot_port_mode_changed(p_store->mode);
    }

    if (mode_is_tracking(p_store->mode))
    {
        handle_pid_motion(p_coords, p_store);
    }
    else
    {
        motion_stop(&p_store->motion);
        pathbot_port_motion_apply(&p_store->motion);
    }

    return PATHBOT_RESULT_OK;
}

static inline void
handle_pid_motion(pathbot_coords_t const * const p_coords,
                  pathbot_store_t * const        p_store)
{
    int8_t              error         = coords_compute_mass_center(p_coords);
    stack_t            *p_past_errors = &p_store->past_errors;
    pathbot_pid_conf_t *p_pid         = &p_store->pid_conf;

    if (motion_update_pid(error, p_past_errors, p_pid, &p_store->motion))
    {
        pathbot_port_motion_apply(&p_store->motion);
    }

    stack_push_rolling(p_past_errors, error);
}
