#include "coords.h"
#include "mode.h"
#include "motion.h"
#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>
#include <stdint.h>

static inline void
handle_finish(pathbot_coords_t const * const p_coords,
              pathbot_store_t * const        p_store);

static inline void
handle_tracking(pathbot_coords_t const * const p_coords,
                pathbot_store_t * const        p_store);

int
pathbot_handle_coords(pathbot_coords_t const * const p_coords)
{
    pathbot_store_t *p_store = pathbot_store_get();

    if (pathbot_mode_is_tracking(p_store->mode))
    {
        handle_finish(p_coords, p_store);
        handle_tracking(p_coords, p_store);
    }

    if (mode_update_tracking(p_coords, &p_store->mode))
    {
        pathbot_port_mode_changed(p_store->mode);
    }

    return PATHBOT_RESULT_OK;
}

static inline void
handle_finish(pathbot_coords_t const * const p_coords,
              pathbot_store_t * const        p_store)
{
    if (coords_is_on_finish(p_coords))
    {
        p_store->motion.direction  = PATHBOT_DIRECTION_NONE;
        p_store->motion.correction = 0;
        pathbot_port_motion_apply(&p_store->motion);
    }
}

static inline void
handle_tracking(pathbot_coords_t const * const p_coords,
                pathbot_store_t * const        p_store)
{
    if (!coords_is_on_finish(p_coords))
    {
        int8_t error = stack_peek_or(&p_store->past_errors, 0);
        coords_compute_mass_center(p_coords, &error);

        if (motion_update_pid(error,
                              &p_store->past_errors,
                              &p_store->pid_conf,
                              &p_store->motion))
        {
            pathbot_port_motion_apply(&p_store->motion);
        }

        stack_push_rolling(&p_store->past_errors, error);
    }
}
