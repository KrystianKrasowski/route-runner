#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/motion_port.hpp"

namespace linebot
{

class motion_api
{
public:

    static motion_api&
    of(data_store& store, motion_port& port);

    void
    apply(commands remote_control);

    void
    apply(coordinates line_position);

private:

    data_store&  store_;
    motion_port& port_;

    motion_api(data_store& store, motion_port& port)
        : store_{store},
          port_{port}
    {
    }
};

} // namespace linebot
