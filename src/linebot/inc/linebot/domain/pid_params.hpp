#pragma once

#include <cstdint>

namespace linebot
{

struct pid_params
{
    static constexpr uint8_t FIXED_POINT_BASE = 100;

    uint16_t kp;
    uint16_t ki;
    uint16_t kd;

    bool
    operator==(const pid_params& other) const
    {
        return kp == other.kp && ki == other.ki && kd == other.kd;
    }
};

} // namespace linebot
