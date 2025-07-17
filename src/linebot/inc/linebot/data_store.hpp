#pragma once

#include "linebot/domain/commands.hpp"

namespace linebot
{

struct data_store
{
    commands remote_control_ = commands{commands::NONE};
};

} // namespace linebot
