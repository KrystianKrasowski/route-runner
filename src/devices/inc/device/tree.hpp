#pragma once

#include "device/isr_event_emitter.hpp"
#include "device/l293.hpp"
#include "device/qtrhd06a.hpp"
#include "device/shell.hpp"
#include "device/timeout.hpp"
#include "dualshock2.hpp"
#include "toggle_sequence.hpp"

namespace device
{

struct tree
{
    toggle_sequence& blink_;
    dualshock2&      remote_control_;
    l293&            motor_left_;
    l293&            motor_right_;
    qtrhd06a&        line_sensor_;
    timeout&         offroute_timeout_;
    shell&           shell_;

    static tree
    of(isr_event_emitter& events);

    void
    init(isr_event_emitter& events);
};

extern tree g_device_tree;

} // namespace device
