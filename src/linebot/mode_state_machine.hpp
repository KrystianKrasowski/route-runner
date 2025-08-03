#pragma once

#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/mode_control.hpp"

namespace linebot
{

class mode_state_machine
{
public:

    explicit mode_state_machine(mode& current_mode)
        : mode_{current_mode}
    {
    }

    bool
    transit(const mode_control control)
    {
        return maybe_switch_to_following(control)
            || maybe_switch_to_manual(control);
    }

    bool
    transit(const coordinates& line_position)
    {
        return maybe_switch_to_manual(line_position)
            || maybe_switch_to_detected(line_position)
            || maybe_switch_to_recovering(line_position)
            || maybe_switch_to_following(line_position);
    }

private:

    mode& mode_;

    bool
    maybe_switch_to_following(const mode_control control)
    {
        if (control.has_follow() && mode_.is_line_detected())
        {
            mode_ = mode::FOLLOWING;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_manual(const mode_control control)
    {
        if (control.has_break() && mode_.is_tracking())
        {
            mode_ = mode::MANUAL;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_manual(const coordinates& line_position)
    {
        if (mode_.is_line_detected() && !line_position.is_on_route())
        {
            mode_ = mode::MANUAL;
            return true;
        }

        if (mode_.is_tracking() && line_position.is_on_finish())
        {
            mode_ = mode::MANUAL;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_detected(const coordinates& line_position)
    {
        if (mode_.is_manual() && line_position.is_on_route())
        {
            mode_ = mode::LINE_DETECTED;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_recovering(const coordinates& line_position)
    {
        if (mode_.is_following() && !line_position.is_on_route())
        {
            mode_ = mode::RECOVERING;
            return true;
        }

        return false;
    }

    bool
    maybe_switch_to_following(const coordinates& line_position)
    {
        if (mode_.is_recovering() && line_position.is_on_route())
        {
            mode_ = mode::FOLLOWING;
            return true;
        }

        return false;
    }
};

} // namespace linebot
