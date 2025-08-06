#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/actions.hpp"
#include "linebot/domain/remote_control.hpp"

namespace linebot
{

class actions_dispatcher
{
public:

    actions_dispatcher(const data_store& store)
        : store_{store}
    {
    }

    actions
    query(const remote_control commands)
    {
        uint8_t values = actions::NONE;

        maybe_apply_maneuver(commands, values);
        maybe_tune_pid(commands, values);
        maybe_change_mode(commands, values);

        return actions{values};
    }

private:

    const data_store& store_;

    void
    maybe_apply_maneuver(const remote_control commands, uint8_t& values)
    {
        bool is_same_move     = commands.has_same_move(store_.remote_control_);
        bool is_tracking_mode = store_.mode_.is_tracking();
        bool is_stop          = commands.has_break();

        if ((!is_same_move && !is_tracking_mode) || is_stop)
        {
            values |= actions::APPLY_MANEUVER;
        }
    }

    void
    maybe_tune_pid(const remote_control commands, uint8_t& values)
    {
        if (!commands.has_same_pid_tuning(store_.remote_control_))
        {
            values |= actions::TUNE_PID;
        }
    }

    void
    maybe_change_mode(const remote_control commands, uint8_t& values)
    {
        if (!commands.has_same_mode_transition(store_.remote_control_))
        {
            values |= actions::CHANGE_MODE;
        }
    }
};

} // namespace linebot
