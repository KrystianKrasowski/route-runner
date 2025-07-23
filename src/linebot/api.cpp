#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "maneuver_factory.hpp"
#include "mode_state_machine.hpp"

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
        maneuver motion        = create_maneuver(remote_control);
        motion_.apply(motion);
    }
}

void
api::attempt_maneuver(coordinates& line_position)
{
    if (store_.mode_.is_tracking())
    {
        maneuver motion = create_maneuver(line_position);
        store_.errors_.push(motion.get_correction());
        motion_.apply(motion);
    }
}

void
api::attempt_mode_switch(commands remote_control)
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(remote_control))
    {
        status_indicator_.apply(store_.mode_);
    }
}

void
api::attempt_mode_switch(coordinates& line_position)
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(line_position))
    {
        status_indicator_.apply(store_.mode_);
    }
}

bool
api::is_maneuver_applicable(commands remote_control)
{
    return store_.remote_control_ != remote_control
        && !store_.mode_.is_tracking();
}

} // namespace linebot
