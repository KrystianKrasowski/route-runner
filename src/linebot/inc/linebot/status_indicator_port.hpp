#pragma once

#include "linebot/domain/mode.hpp"

namespace linebot
{

struct status_indicator_port
{
    virtual void
    apply(mode mode) = 0;
};

} // namespace linebot
