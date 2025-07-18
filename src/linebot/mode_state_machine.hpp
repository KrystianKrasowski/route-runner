#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/mode.hpp"

namespace linebot
{

class mode_state_machine
{
public:

    mode_state_machine(mode& current_mode)
        : mode_{current_mode}
    {
    }

    bool
    transit(commands remote_control)
    {
        return maybe_switch_to_following(remote_control)
            || maybe_switch_to_manual(remote_control);
    }

private:

    mode& mode_;

    bool
    maybe_switch_to_following(commands remote_control)
    {
        if (remote_control.have_follow() && mode_.is_line_detected())
        {
            mode_ = mode::FOLLOWING;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_manual(commands remote_control)
    {
        if (remote_control.have_break() && mode_.is_tracking())
        {
            mode_ = mode::MANUAL;
            return true;
        }

        return false;
    }
};

} // namespace linebot
