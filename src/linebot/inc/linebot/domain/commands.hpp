#pragma once

#include <cstdint>

namespace linebot
{

struct commands
{
    enum command
    {
        STOP      = 1,
        FORWARD   = 2,
        BACKWARD  = 4,
        LEFT      = 8,
        RIGHT     = 16,
        BREAK     = 32,
        FOLLOW    = 64,
    };

    bool
    operator==(const commands& other) const
    {
        return value_ == other.value_;
    }

    explicit commands(uint16_t value)
        : value_{value}
    {
    }

    uint16_t
    to_uint16() const
    {
        return value_;
    }

    bool
    have_forward() const
    {
        return (value_ & FORWARD) && !(value_ & BACKWARD);
    }

    bool
    have_backward() const
    {
        return (value_ & BACKWARD) && !(value_ & FORWARD);
    }

    bool
    have_left() const
    {
        return (value_ & LEFT) && !(value_ & RIGHT);
    }

    bool
    have_right() const
    {
        return (value_ & RIGHT) && !(value_ & LEFT);
    }

    bool
    have_move() const
    {
        return have_forward() || have_backward();
    }

    bool
    have_break() const
    {
        return value_ & BREAK;
    }

    bool
    have_follow() const
    {
        return value_ & FOLLOW;
    }

private:

    uint16_t value_;
};

} // namespace linebot
