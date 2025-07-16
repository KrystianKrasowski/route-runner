#pragma once

#include "linebot/domain/commands.hpp"

namespace linebot
{

struct data_store
{
    commands commands_ = commands{commands::NONE};
};

} // namespace linebot
