#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>
#include <etl/circular_buffer.h>

namespace linebot
{

struct data_store
{
    etl::circular_buffer<int16_t, 20> errors_;

    commands   remote_control_ = commands{commands::STOP};
    mode       mode_           = mode::MANUAL;
    pid_params pid_params_     = pid_params{0.7, 0, 4.1};
};

} // namespace linebot
