#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/mode_control.hpp"
#include <cstdint>

namespace mapper
{

inline linebot::mode_control
map_mode_control(uint16_t raw)
{
    uint8_t values = 0;

    if (raw & device::dualshock2::CROSS)
    {
        values |= linebot::mode_control::BREAK;
    }

    if (raw & device::dualshock2::START)
    {
        values |= linebot::mode_control::FOLLOW;
    }

    return linebot::mode_control{values};
}

} // namespace mapper
