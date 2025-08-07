#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/actions.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/remote_control.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/printer_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"

namespace linebot
{

class api
{
public:

    static api&
    of(data_store&            store,
       motion_port&           motion,
       status_indicator_port& status_indicator,
       route_guard_port&      route_guard,
       printer_port&          printer);

    actions
    query(remote_control commands);

    actions
    query(coordinates line_position);

    void
    apply_motion_by_remote();

    void
    switch_mode_by_remote();

    void
    tune_pid_regulator();

    void
    apply_motion_by_line_position();

    void
    switch_mode_by_line_position();

    void
    toggle_route_guard();

    void
    halt();

    void
    dump_store();

private:

    data_store&            store_;
    motion_port&           motion_;
    status_indicator_port& status_indicator_;
    route_guard_port&      route_guard_;
    printer_port&          printer_;

    api(data_store&            store,
        motion_port&           motion,
        status_indicator_port& status_indicator,
        route_guard_port&      route_guard,
        printer_port&          printer)
        : store_{store},
          motion_{motion},
          status_indicator_{status_indicator},
          route_guard_{route_guard},
          printer_{printer}
    {
    }
};

} // namespace linebot
