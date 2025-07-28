#pragma once

#include "linebot/route_guard_port.hpp"

namespace linebot
{

struct route_guard_port_mock : public route_guard_port
{
    bool started = false;
    bool stopped = false;

    void
    start() override
    {
        started = true;
        stopped = false;
    }

    void
    stop() override
    {
        started = false;
        stopped = true;
    }
};

} // namespace linebot
