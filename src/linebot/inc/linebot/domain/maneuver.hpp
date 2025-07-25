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

    maneuver(direction direction, int8_t correction)
        : direction_{direction},
          correction_{correction}
    {
    }

    direction
    get_direction() const
    {
        return direction_;
    }

    int8_t
    get_correction() const
    {
        return correction_;
    }

    bool
    is_forward() const
    {
        return direction_ == FORWARD;
    }

    bool
    is_backward() const
    {
        return direction_ == BACKWARD;
    }

    bool
    is_correction_above(int8_t value) const
    {
        return correction_ > value;
    }

    bool
    is_correction_below(int8_t value) const
    {
        return correction_ < value;
    }

    bool
    is_correction_at(int8_t value) const
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
