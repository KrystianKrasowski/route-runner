#pragma once

#include "linebot/domain/pid_params.hpp"
#include "linebot/domain/remote_control.hpp"
#include <cstdint>

namespace linebot
{

class pid_tuner
{
public:

    pid_tuner(const remote_control& control, pid_params& params)
        : params_{params},
          control_{control}
    {
    }

    void
    tune_proportional()
    {
        if (control_.has_kp_up())
        {
            params_.kp_ += TUNE_STEP_KP;
        }

        if (control_.has_kp_down())
        {
            params_.kp_ -= TUNE_STEP_KP;
        }
    }

    void
    tune_integral()
    {
        if (control_.has_ki_up())
        {
            params_.ki_ += TUNE_STEP_KI;
        }

        if (control_.has_ki_down())
        {
            params_.ki_ -= TUNE_STEP_KI;
        }
    }

    void
    tune_derivative()
    {
        if (control_.has_kd_up())
        {
            params_.kd_ += TUNE_STEP_KD;
        }

        if (control_.has_kd_down())
        {
            params_.kd_ -= TUNE_STEP_KD;
        }
    }

private:

    static constexpr uint8_t TUNE_STEP_KP = 10;
    static constexpr uint8_t TUNE_STEP_KI = 1;
    static constexpr uint8_t TUNE_STEP_KD = 100;

    pid_params&          params_;
    const remote_control control_;
};

} // namespace linebot
