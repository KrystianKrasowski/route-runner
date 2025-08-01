#pragma once

#include <cstdint>

namespace linebot
{

struct pid_params
{
    static constexpr uint16_t FIXED_POINT_BASE = 1000;

    uint16_t kp_;
    uint16_t ki_;
    uint16_t kd_;

    bool
    operator==(const pid_params& other) const
    {
        return kp_ == other.kp_ && ki_ == other.ki_ && kd_ == other.kd_;
    }
};

} // namespace linebot
