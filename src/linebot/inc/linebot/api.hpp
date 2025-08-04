#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/actions.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/mode_control.hpp"
#include "linebot/domain/motion_control.hpp"
#include "linebot/domain/pid_control.hpp"
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
    dispatch(const remote_control commands);

    void
    attempt_maneuver(const motion_control control);

    void
    attempt_maneuver(const coordinates& line_positon);

    void
    attempt_mode_switch(const mode_control control);

    void
    attempt_mode_switch(const coordinates& line_position);

    void
    attempt_route_guard_toggle(const coordinates& line_position);

    void
    halt();

    void
    dump_store();

    void
    tune_pid_regulator(const pid_control control);

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

    inline bool
    is_applicable(const motion_control control);

    inline bool
    is_applicable(const pid_control control);
};

} // namespace linebot
