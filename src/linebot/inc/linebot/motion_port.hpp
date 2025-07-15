#pragma once

namespace linebot
{

struct maneuver;

// TODO: Consider using callback mechanism instead, etl::function
class motion_port
{
public:

    virtual void
    apply(maneuver& motion) = 0;
};

} // namespace linebot
