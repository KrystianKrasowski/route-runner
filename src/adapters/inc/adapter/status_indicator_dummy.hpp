#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/status_indicator_port.hpp"

namespace adapter
{

class status_indicator_dummy : public linebot::status_indicator_port
{
public:

    static status_indicator_dummy&
    of();

    void
    apply(linebot::mode mode) override;
};

} // namespace adapter
