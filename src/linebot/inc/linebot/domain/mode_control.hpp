#pragma once

#include <cstdint>

namespace linebot
{

struct mode_control
{
    enum command
    {
        BREAK  = 1,
        FOLLOW = 2,
    };

    explicit mode_control(uint8_t value)
        : value_{value}
    {
    }

    bool
    operator==(const mode_control& other) const
    {
        return value_ == other.value_;
    }

    bool
    operator!=(const mode_control& other) const
    {
        return value_ != other.value_;
    }

    bool
    has_break() const
    {
        return value_ & BREAK;
    }

    bool
    has_follow() const
    {
        return value_ & FOLLOW;
    }

private:

    const uint8_t value_;
};

} // namespace linebot
