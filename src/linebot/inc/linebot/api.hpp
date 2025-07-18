#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/status_indicator_port.hpp"

namespace linebot
{

class api
{
public:

    static api&
    of(data_store&            store,
       motion_port&           motion_port,
       status_indicator_port& status_indicator);

    void
    attempt_maneuver(commands remote_control);

    void
    attempt_mode_switch(commands remote_control);

private:

    data_store&            store_;
    motion_port&           motion_;
    status_indicator_port& status_indicator_;

    api(data_store&            store,
        motion_port&           motion,
        status_indicator_port& status_indicator)
        : store_{store},
          motion_{motion},
          status_indicator_{status_indicator}
    {
    }

    inline bool
    is_maneuver_applicable(commands remote_control);

    inline bool
    is_mode_to_following_switchable(commands remote_control);

    inline bool
    is_mode_to_manual_switchable(commands remote_control);
};

} // namespace linebot
