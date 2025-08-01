#pragma once

#include "linebot/domain/maneuver.hpp"

namespace linebot
{

class motion_port
{
public:

    virtual void
    apply(maneuver motion) = 0;
};

} // namespace linebot
