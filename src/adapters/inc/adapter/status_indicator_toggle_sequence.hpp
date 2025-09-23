#pragma once

#include "device/toggle_sequence.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/status_indicator_port.hpp"

namespace adapter
{

class status_indicator_toggle_sequence : public linebot::status_indicator_port
{
public:

    static status_indicator_toggle_sequence&
    of(const device::toggle_sequence& blink);

    void
    apply(linebot::mode mode) override;

private:

    const device::toggle_sequence& blink_;

    status_indicator_toggle_sequence(const device::toggle_sequence& blink)
        : blink_{blink}
    {
    }
};

} // namespace adapter
