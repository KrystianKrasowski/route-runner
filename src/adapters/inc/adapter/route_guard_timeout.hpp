#pragma once

#include "linebot/route_guard_port.hpp"

namespace adapter
{

class route_guard_timeout : public linebot::route_guard_port
{
public:
    static route_guard_timeout&
    of();

    void
    start() override;

    void
    stop() override;
};

} // namespace adapter
