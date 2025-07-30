#pragma once

#include "linebot/domain/pid_control.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>

namespace linebot
{

class pid_tuner
{
public:

    pid_tuner(const pid_control control, pid_params& params)
        : control_{control},
          params_{params}
    {
    }

    void
    tune_proportional()
    {
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

    const pid_control control_;
    pid_params&       params_;
};

} // namespace linebot
