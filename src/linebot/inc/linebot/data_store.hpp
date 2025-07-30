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
    static constexpr uint8_t ERROR_HISTORY_LENGTH = 20;

    etl::circular_buffer<int8_t, ERROR_HISTORY_LENGTH> errors_;

    command    remote_control_ = command{command::STOP};
    mode       mode_           = mode::MANUAL;
    pid_params pid_params_     = pid_params{70, 0, 410};
};

} // namespace linebot
