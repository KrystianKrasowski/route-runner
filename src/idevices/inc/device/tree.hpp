#pragma once

#include "device/isr_event_emitter.hpp"
#include "dualshock2.hpp"
#include "toggle_sequence.hpp"

namespace device
{

struct tree
{
    toggle_sequence& toggle_sequence_;
    dualshock2&      dualshock2_;

    static tree
    of(isr_event_emitter& events);
};

} // namespace device
