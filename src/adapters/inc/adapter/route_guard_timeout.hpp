#pragma once

#include "device/timeout.hpp"
#include "linebot/route_guard_port.hpp"

namespace adapter
{

class route_guard_timeout : public linebot::route_guard_port
{
public:

    static route_guard_timeout&
    of(device::timeout const & offroute_timeout);

    void
    start() override;

    void
    stop() override;

private:

    device::timeout const & offroute_timeout_;

    route_guard_timeout(device::timeout const & offroute_timeout)
        : offroute_timeout_{offroute_timeout}
    {
    }
};

} // namespace adapter
