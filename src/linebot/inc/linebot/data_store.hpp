#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/domain/motion_control.hpp"
#include "linebot/domain/pid_control.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>
#include <etl/circular_buffer.h>

namespace linebot
{

struct data_store
{
    static constexpr uint8_t ERROR_HISTORY_LENGTH{10};

    etl::circular_buffer<int8_t, ERROR_HISTORY_LENGTH> errors_;

    motion_control motion_control_{motion_control::STOP};
    pid_control    pid_control_{pid_control::NONE};
    mode           mode_{mode::MANUAL};
    pid_params     pid_params_{700, 0, 4100};
};

} // namespace linebot
