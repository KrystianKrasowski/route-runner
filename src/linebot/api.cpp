#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/motion_control.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/printer_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "maneuver_factory.hpp"
#include "mode_state_machine.hpp"
#include "pid_regulator.hpp"
#include "pid_tuner.hpp"

namespace linebot
{

api&
api::of(
    data_store&            store,
    motion_port&           motion,
    status_indicator_port& status_indicator,
    route_guard_port&      route_guard,
    printer_port&          printer
)
{
    static api api{store, motion, status_indicator, route_guard, printer};

    status_indicator.apply(store.mode_);

    return api;
}

void
api::attempt_maneuver(motion_control control)
{
    if (is_maneuver_applicable(control))
    {
        store_.motion_control_ = control;
        maneuver motion        = create_maneuver(control);
        motion_.apply(motion);
    }
}

void
api::attempt_maneuver(const coordinates& line_position)
{
    if (store_.mode_.is_tracking())
    {
        pid_regulator pid{store_.pid_params_, store_.errors_};

        maneuver motion = create_maneuver(line_position, pid);
        motion_.apply(motion);
    }
}

void
api::attempt_mode_switch(motion_control control)
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(control))
    {
        status_indicator_.apply(store_.mode_);
    }
}

void
api::attempt_mode_switch(const coordinates& line_position)
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(line_position))
    {
        status_indicator_.apply(store_.mode_);
    }
}

void
api::attempt_route_guard_toggle(const coordinates& line_position)
{
    if (store_.mode_.is_following() && !line_position.is_on_route())
    {
        route_guard_.start();
    }

    if (store_.mode_.is_recovering() && line_position.is_on_route())
    {
        route_guard_.stop();
    }
}

void
api::halt()
{
    motion_control stop{motion_control::STOP};

    store_.mode_           = mode::MANUAL;
    store_.motion_control_ = stop;
    maneuver motion        = create_maneuver(stop);

    motion_.apply(motion);
    status_indicator_.apply(store_.mode_);
    route_guard_.stop();
}

void
api::dump_store()
{
    printer_.print(store_.mode_);
    printer_.print(store_.pid_params_);
}

void
api::tune_pid_regulator(const motion_control control)
{
    if (control.has_pid_kp_up() && !locked_)
    {
        locked_                 = true;
        store_.pid_params_.kp_ += 5;
    }

    else if (control.has_pid_kp_down() && !locked_)
    {
        locked_                 = true;
        store_.pid_params_.kp_ -= 5;
    }
}

bool
api::is_maneuver_applicable(motion_control control)
{
    return store_.motion_control_ != control && !store_.mode_.is_tracking();
}

} // namespace linebo
