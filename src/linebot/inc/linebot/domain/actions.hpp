#pragma once

#include <cstdint>

namespace linebot
{

struct actions
{
    enum value
    {
        NONE           = 0,
        APPLY_MANEUVER = 1,
        TUNE_PID       = 2,
        CHANGE_MODE    = 4,
    };

    actions(uint8_t values)
        : values_{values}
    {
    }

    uint8_t
    as_uint() const
    {
        return values_;
    }

    bool
    contain(uint8_t value) const
    {
        return (values_ & value) == value;
    }

private:

    uint8_t values_;
};

} // namespace linebot
