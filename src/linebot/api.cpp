#include "linebot/api.hpp"
#include "actions_dispatcher.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
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

actions
api::query(remote_control commands)
{
    actions_dispatcher dispatcher{store_};
    auto               actions = dispatcher.query(commands);

    store_.remote_control_ = commands;

    return actions;
}

actions
api::query(const coordinates& line_position)
{
    store_.line_position_ = line_position;

    uint8_t values = 0;

    values |= actions::CHANGE_MODE_BY_COORDS;
    values |= actions::ROUTE_GUARD_TOGGLE;

    if (store_.mode_.is_tracking())
    {
        values |= actions::APPLY_MANEUVER_BY_COORDS;
    }

    return actions{values};
}

void
api::apply_motion_by_remote()
{
    maneuver motion = create_maneuver(store_.remote_control_);
    motion_.apply(motion);
}

void
api::switch_mode_by_remote()
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(store_.remote_control_))
    {
        status_indicator_.apply(store_.mode_);
    }
}

void
api::tune_pid_regulator()
{
    pid_tuner tuner{store_.remote_control_, store_.pid_params_};
    tuner.tune_proportional();
    tuner.tune_integral();
    tuner.tune_derivative();
}

void
api::apply_motion_by_line_position()
{
    pid_regulator pid{store_.pid_params_, store_.errors_};

    maneuver motion = create_maneuver(store_.line_position_, pid);
    motion_.apply(motion);
}

void
api::switch_mode_by_line_position()
{
    mode_state_machine mode_transition{store_.mode_};

    if (mode_transition.transit(store_.line_position_))
    {
        status_indicator_.apply(store_.mode_);
    }
}

void
api::toggle_route_guard()
{
    if (store_.mode_.is_following() && !store_.line_position_.is_on_route())
    {
        route_guard_.start();
    }

    if (store_.mode_.is_recovering() && store_.line_position_.is_on_route())
    {
        route_guard_.stop();
    }
}

void
api::halt()
{
    remote_control stop{remote_control::STOP};

    store_.mode_           = mode::MANUAL;
    store_.remote_control_ = stop;
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

} // namespace linebot
