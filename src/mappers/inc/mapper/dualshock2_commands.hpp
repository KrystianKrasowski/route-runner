#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/commands.hpp"
#include <cstdint>

namespace mapper
{

inline linebot::commands
map(uint16_t raw)
{
    uint16_t commands = 0;

    if (raw & device::dualshock2::R2)
    {
        commands |= linebot::commands::FORWARD;
    }

    if (raw & device::dualshock2::L2)
    {
        commands |= linebot::commands::BACKWARD;
    }

    if (raw & device::dualshock2::RIGHT)
    {
        commands |= linebot::commands::RIGHT;
    }

    if (raw & device::dualshock2::LEFT)
    {
        commands |= linebot::commands::LEFT;
    }

    if (raw & device::dualshock2::CROSS)
    {
        commands |= linebot::commands::BREAK;
    }

    if (raw & device::dualshock2::START)
    {
        commands |= linebot::commands::FOLLOW;
    }

    return linebot::commands{commands};
}

} // namespace mapper
