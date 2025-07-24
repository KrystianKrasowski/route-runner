#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"

namespace linebot
{

class api
{
public:

    static api&
    of(data_store&            store,
       motion_port&           motion_port,
       status_indicator_port& status_indicator,
       route_guard_port&      route_guard);

    void
    attempt_maneuver(commands remote_control);

    void
    attempt_maneuver(coordinates& line_positon);

    void
    attempt_mode_switch(commands remote_control);

    void
    attempt_mode_switch(const coordinates& line_position);

    void
    attempt_route_guard_toggle(const coordinates& line_position);

private:

    data_store&            store_;
    motion_port&           motion_;
    status_indicator_port& status_indicator_;
    route_guard_port&      route_guard_;

    api(data_store&            store,
        motion_port&           motion,
        status_indicator_port& status_indicator,
        route_guard_port&      route_guard)
        : store_{store},
          motion_{motion},
          status_indicator_{status_indicator},
          route_guard_{route_guard}
    {
    }

    bool
    is_maneuver_applicable(commands remote_control);
};

} // namespace linebot
