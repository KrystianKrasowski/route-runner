#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/motion_control.hpp"
#include <cstdint>

namespace mapper
{

inline linebot::motion_control
map_motion_control(uint16_t raw)
{
    uint16_t values = 0;

    if (raw & device::dualshock2::R2)
    {
        values |= linebot::motion_control::FORWARD;
    }

    if (raw & device::dualshock2::L2)
    {
        values |= linebot::motion_control::BACKWARD;
    }

    if (raw & device::dualshock2::RIGHT)
    {
        values |= linebot::motion_control::RIGHT;
    }

    if (raw & device::dualshock2::LEFT)
    {
        values |= linebot::motion_control::LEFT;
    }

    if (raw & device::dualshock2::CROSS)
    {
        values |= linebot::motion_control::BREAK;
    }

    if (raw & device::dualshock2::START)
    {
        values |= linebot::motion_control::FOLLOW;
    }

    return linebot::motion_control{values};
}

} // namespace mapper
