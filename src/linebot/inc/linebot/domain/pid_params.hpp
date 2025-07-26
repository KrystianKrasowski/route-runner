#pragma once

namespace linebot
{

struct pid_params
{
    float kp;
    float ki;
    float kd;

    bool
    operator==(const pid_params& other) const
    {
        return kp == other.kp && ki == other.ki && kd == other.kd;
    }
};

} // namespace linebot
