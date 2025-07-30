#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/commands.hpp"
#include <cstdint>

namespace mapper
{

inline linebot::command
map(uint16_t raw)
{
    uint16_t values = 0;

    if (raw & device::dualshock2::R2)
    {
        values |= linebot::command::FORWARD;
    }

    if (raw & device::dualshock2::L2)
    {
        values |= linebot::command::BACKWARD;
    }

    if (raw & device::dualshock2::RIGHT)
    {
        values |= linebot::command::RIGHT;
    }

    if (raw & device::dualshock2::LEFT)
    {
        values |= linebot::command::LEFT;
    }

    if (raw & device::dualshock2::CROSS)
    {
        values |= linebot::command::BREAK;
    }

    if (raw & device::dualshock2::START)
    {
        values |= linebot::command::FOLLOW;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::command::PID_KP_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::command::PID_KP_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::command::PID_KI_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::command::PID_KI_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::command::PID_KD_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::command::PID_KD_UP;
    }

    return linebot::command{values};
}

} // namespace mapper
