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

    return linebot::command{values};
}

} // namespace mapper
