#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/motion_port.hpp"

namespace linebot
{

class api
{
public:

    static api&
    of(data_store& store, motion_port& motion_port);

    void
    attempt_maneuver(commands remote_control);

private:

    data_store&  store_;
    motion_port& motion_port_;

    api(data_store& store, motion_port& motion_port)
        : store_{store},
          motion_port_{motion_port}
    {
    }
};

} // namespace linebot
