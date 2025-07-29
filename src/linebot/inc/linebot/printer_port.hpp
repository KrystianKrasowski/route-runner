#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"

namespace linebot
{

struct printer_port
{
    virtual void
    print(mode mode) = 0;

    virtual void
    print(pid_params& pid) = 0;
};

} // namespace linebot
