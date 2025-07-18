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

    constexpr
    operator value() const
    {
        return value_;
    }

    constexpr bool
    is_tracking()
    {
        return value_ == FOLLOWING || value_ == RECOVERING;
    }

    constexpr bool
    is_line_detected()
    {
        return value_ == LINE_DETECTED;
    }

private:

    mode::value value_ = MANUAL;
};

} // namespace linebot
