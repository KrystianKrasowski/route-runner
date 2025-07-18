#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "maneuver_factory.hpp"

namespace linebot
{

api&
api::of(
    data_store&            store,
    motion_port&           port,
    status_indicator_port& status_indicator
)
{
    static api api{store, port, status_indicator};
    return api;
}

void
api::attempt_maneuver(commands remote_control)
{
    if (is_maneuver_applicable(remote_control))
    {
        store_.remote_control_ = remote_control;
        maneuver maneuver      = create_maneuver(remote_control);
        motion_.apply(maneuver);
    }
}

void
api::attempt_mode_switch(commands remote_control)
{
    if (is_mode_to_following_switchable(remote_control))
    {
        store_.mode_ = mode::FOLLOWING;
        status_indicator_.apply(mode::FOLLOWING);
    }

    if (is_mode_to_manual_switchable(remote_control))
    {
        store_.mode_ = mode::MANUAL;
        status_indicator_.apply(mode::MANUAL);
    }
}

bool
api::is_maneuver_applicable(commands remote_control)
{
    return store_.remote_control_ != remote_control
        && !store_.mode_.is_tracking();
}

bool
api::is_mode_to_following_switchable(commands remote_control)
{
    return remote_control.have_follow() && store_.mode_.is_line_detected();
}

bool
api::is_mode_to_manual_switchable(commands remote_control)
{
    return remote_control.have_break() && store_.mode_.is_tracking();
}

} // namespace linebot
