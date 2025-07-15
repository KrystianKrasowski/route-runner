#pragma once

#include <cstdint>

namespace linebot
{

struct maneuver
{
    enum direction
    {
        NONE = 0,
        FORWARD,
        BACKWARD,
    };

    const direction direction_;
    const int8_t    correction_;

    static maneuver
    forward(int8_t correction)
    {
        return maneuver{FORWARD, correction};
    }

    static maneuver
    backward(int8_t correction)
    {
        return maneuver{BACKWARD, correction};
    }

    static maneuver
    none()
    {
        return maneuver{NONE, 0};
    }

    bool
    operator==(const maneuver&) const = default;
};

} // namespace linebot
