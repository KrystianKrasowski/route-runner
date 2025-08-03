#pragma once

#include <cstdint>

namespace linebot
{

struct motion_control
{
    enum command
    {
        STOP     = 1,
        FORWARD  = 2,
        BACKWARD = 4,
        LEFT     = 8,
        RIGHT    = 16,
    };

    explicit motion_control(uint8_t value)
        : value_{value}
    {
    }

    bool
    operator==(const motion_control& other) const
    {
        return value_ == other.value_;
    }

    bool
    operator!=(const motion_control& other) const
    {
        return value_ != other.value_;
    }

    uint8_t
    to_int() const
    {
        return value_;
    }

    bool
    has_forward() const
    {
        return (value_ & FORWARD) && !(value_ & BACKWARD);
    }

    bool
    has_backward() const
    {
        return (value_ & BACKWARD) && !(value_ & FORWARD);
    }

    bool
    has_left() const
    {
        return (value_ & LEFT) && !(value_ & RIGHT);
    }

    bool
    has_right() const
    {
        return (value_ & RIGHT) && !(value_ & LEFT);
    }

    bool
    has_move() const
    {
        return has_forward() || has_backward();
    }

private:

    uint8_t value_;
};

} // namespace linebot
