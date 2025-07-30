#pragma once

#include "linebot/domain/motion_control.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>

namespace linebot
{

class pid_tuner
{
public:

    pid_tuner(const motion_control control, pid_params& params)
        : motion_control_{control},
          params_{params}
    {
    }

    void
    tune_proportional()
    {
        bool has_kp_up =
            motion_control_.to_uint16() & motion_control::PID_KD_UP;
        bool has_kp_down =
            motion_control_.to_uint16() & motion_control::PID_KD_DOWN;

        if (!is_locked_)
        {
            params_.kp_++;
        }

        return;

        if (has_kp_up && !is_locked_)
        {
            params_.kp_ += TUNE_STEP;
            is_locked_   = true;
        }

        if (has_kp_down && !is_locked_)
        {
            params_.kp_ -= TUNE_STEP;
            is_locked_   = true;
        }
    }

    void
    tune_integral()
    {
    }

    void
    tune_derivative()
    {
    }

private:

    static constexpr uint8_t TUNE_STEP = 5;

    const motion_control motion_control_;
    pid_params&          params_;

    bool is_locked_ = false;
};

} // namespace linebot
