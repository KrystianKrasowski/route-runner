#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include "maneuver_factory.hpp"

namespace linebot
{

api&
api::of(data_store& store, motion_port& port)
{
    static api api{store, port};
    return api;
}

void
api::attempt_maneuver(commands remote_control)
{
    if (is_maneuver_applicable(remote_control))
    {
        store_.remote_control_ = remote_control;
        maneuver maneuver      = create_maneuver(remote_control);
        motion_port_.apply(maneuver);
    }
}

bool
api::is_maneuver_applicable(commands remote_control)
{
    return store_.remote_control_ != remote_control
        && !store_.mode_.is_tracking();
}

} // namespace linebot
