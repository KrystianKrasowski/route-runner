#pragma once

#include <cstdint>

namespace linebot
{

struct pid_control
{
    enum command
    {
        NONE    = 0,
        KP_UP   = 1,
        KP_DOWN = 2,
        KI_UP   = 4,
        KI_DOWN = 8,
        KD_UP   = 16,
        KD_DOWN = 32,
    };

    bool
    operator==(const pid_control& other) const
    {
        return value_ == other.value_;
    }

    bool
    operator!=(const pid_control& other) const
    {
        return !(*this == other);
    }

    explicit pid_control(uint8_t value)
        : value_{value}
    {
    }

    bool
    has_kp_up() const
    {
        return value_ & KP_UP && !(value_ & KP_DOWN);
    }

    bool
    has_kp_down() const
    {
        return value_ & KP_DOWN && !(value_ & KP_UP);
    }

    bool
    has_ki_up() const
    {
        return value_ & KI_UP && !(value_ & KI_DOWN);
    }

    bool
    has_ki_down() const
    {
        return value_ & KI_DOWN && !(value_ & KI_UP);
    }

    bool
    has_kd_up() const
    {
        return value_ & KD_UP && !(value_ & KD_DOWN);
    }

    bool
    has_kd_down() const
    {
        return value_ & KD_DOWN && !(value_ & KD_UP);
    }

private:

    uint8_t value_{NONE};
};

} // namespace linebot
