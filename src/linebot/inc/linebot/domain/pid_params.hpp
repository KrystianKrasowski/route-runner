#pragma once

#include <cstdint>

namespace linebot
{

struct pid_params
{
    static constexpr uint8_t FIXED_POINT_BASE = 100;

    // TODO: Make it fixedpoint integers
    float kp;
    float ki;
    float kd;

    bool
    operator==(const pid_params& other) const
    {
        return kp == other.kp && ki == other.ki && kd == other.kd;
    }

    uint16_t
    get_kp_as_int()
    {
        return kp * FIXED_POINT_BASE;
    }

    uint16_t
    get_ki_as_int()
    {
        return ki * FIXED_POINT_BASE;
    }

    uint16_t
    get_kd_as_int()
    {
        return kd * FIXED_POINT_BASE;
    }
};

} // namespace linebot
