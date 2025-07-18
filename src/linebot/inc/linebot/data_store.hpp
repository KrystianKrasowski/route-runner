#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/mode.hpp"

namespace linebot
{

struct data_store
{
    commands remote_control_ = commands{commands::STOP};
    mode     mode_           = mode::MANUAL;
};

} // namespace linebot
