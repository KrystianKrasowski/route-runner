#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/remote_control.hpp"

namespace mapper
{

inline linebot::remote_control
map_remote_control(uint16_t raw)
{
    uint16_t values = 0;

    if (raw & device::dualshock2::R2)
    {
        values |= linebot::remote_control::FORWARD;
    }

    if (raw & device::dualshock2::L2)
    {
        values |= linebot::remote_control::BACKWARD;
    }

    if (raw & device::dualshock2::RIGHT)
    {
        values |= linebot::remote_control::RIGHT;
    }

    if (raw & device::dualshock2::LEFT)
    {
        values |= linebot::remote_control::LEFT;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::remote_control::KP_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::remote_control::KP_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::remote_control::KI_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::remote_control::KI_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::remote_control::KD_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::remote_control::KD_UP;
    }

    if (raw & device::dualshock2::CROSS)
    {
        values |= linebot::remote_control::BREAK;
    }

    if (raw & device::dualshock2::START)
    {
        values |= linebot::remote_control::FOLLOW;
    }

    return linebot::remote_control{values};
}

} // namespace mapper
