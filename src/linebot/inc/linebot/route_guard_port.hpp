#pragma once

namespace linebot
{

struct route_guard_port
{
    virtual void
    start() = 0;

    virtual void
    stop() = 0;
};

} // namespace linebot
