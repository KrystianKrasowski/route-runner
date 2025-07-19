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

    maneuver(maneuver::direction direction, int8_t correction)
        : direction_{direction},
          correction_{correction}
    {
    }

    // TODO: Check memory footprint
    direction
    get_direction()
    {
        return direction_;
    }

    int8_t
    get_correction()
    {
        return correction_;
    }

    bool
    is_forward()
    {
        return direction_ == FORWARD;
    }

    bool
    is_backward()
    {
        return direction_ == BACKWARD;
    }

    bool
    is_correction_above(int8_t value)
    {
        return correction_ > value;
    }

    bool
    is_correction_below(int8_t value)
    {
        return correction_ < value;
    }

    bool
    is_correction_at(int8_t value)
    {
        return correction_ == value;
    }

    bool
    operator==(const maneuver& other) const
    {
        return direction_ == other.direction_
            && correction_ == other.correction_;
    }

private:

    direction direction_;
    int8_t    correction_;
};

} // namespace linebot
