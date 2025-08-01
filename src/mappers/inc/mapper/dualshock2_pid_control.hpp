#pragma once

#include "device/dualshock2.hpp"
#include "linebot/domain/pid_control.hpp"
#include <cstdint>

namespace mapper
{

inline linebot::pid_control
map_pid_control(uint16_t raw)
{
    uint8_t values = 0;

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::pid_control::KP_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::SQUARE))
    {
        values |= linebot::pid_control::KP_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::pid_control::KI_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::TRIANGLE))
    {
        values |= linebot::pid_control::KI_UP;
    }

    if ((raw & device::dualshock2::L1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::pid_control::KD_DOWN;
    }

    if ((raw & device::dualshock2::R1) && (raw & device::dualshock2::CIRCLE))
    {
        values |= linebot::pid_control::KD_UP;
    }

    return linebot::pid_control{values};
}

} // namespace mapper
