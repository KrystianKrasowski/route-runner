#pragma once

#include <cstdint>

namespace linebot
{

struct remote_control
{
    enum command
    {
        STOP     = 1,
        FORWARD  = 2,
        BACKWARD = 4,
        LEFT     = 8,
        RIGHT    = 16,
        KP_UP    = 32,
        KP_DOWN  = 64,
        KI_UP    = 128,
        KI_DOWN  = 256,
        KD_UP    = 512,
        KD_DOWN  = 1024,
        BREAK    = 2048,
        FOLLOW   = 4096,
    };

    explicit remote_control(uint16_t value)
        : value_{value}
    {
    }

    bool
    operator==(const remote_control& other) const
    {
        return value_ == other.value_;
    }

    bool
    operator!=(const remote_control& other) const
    {
        return value_ != other.value_;
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

    bool
    has_pid_tunning() const
    {
        return has_kp_up() || has_kp_down() || has_ki_up() || has_ki_down()
            || has_kd_up() || has_kd_down();
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

    bool
    has_mode_transition() const
    {
        return has_break() || has_follow();
    }

private:

    uint16_t value_{STOP};
};

} // namespace linebot
