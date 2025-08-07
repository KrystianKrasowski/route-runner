#pragma once

namespace linebot
{

class mode
{
public:

    enum value
    {
        MANUAL = 0,
        LINE_DETECTED,
        FOLLOWING,
        RECOVERING,
    };

    constexpr mode(value val)
        : value_{val}
    {
    }

    // TODO: Remove this implicit converions
    constexpr
    operator value() const
    {
        return value_;
    }

    constexpr bool
    is_line_detected() const
    {
        return value_ == LINE_DETECTED;
    }

    constexpr bool
    is_manual() const
    {
        return value_ == MANUAL;
    }

    constexpr bool
    is_following() const 
    {
        return value_ == FOLLOWING;
    }

    constexpr bool
    is_recovering() const
    {
        return value_ == RECOVERING;
    }

    constexpr bool
    is_tracking() const
    {
        return is_following() || is_recovering();
    }

private:

    mode::value value_ = MANUAL;
};

} // namespace linebot
