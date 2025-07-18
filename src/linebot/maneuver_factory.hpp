#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include <cstdint>

namespace linebot
{

constexpr int8_t CORRECTION_MANUAL_LEFT  = -50;
constexpr int8_t CORRECTION_MANUAL_RIGHT = 50;

inline maneuver
create_maneuver(commands remote_control)
{
    maneuver::direction direction  = maneuver::NONE;
    int8_t              correction = 0;

    if (remote_control.have_left())
    {
        correction = -50;
    }
    else if (remote_control.have_right())
    {
        correction = 50;
    }

    if (remote_control.have_forward())
    {
        direction = maneuver::FORWARD;
    }
    else if (remote_control.have_backward())
    {
        direction = maneuver::BACKWARD;
    }
    else
    {
        direction  = maneuver::NONE;
        correction = 0;
    }

    return {direction, correction};
}

} // namespace linebot
