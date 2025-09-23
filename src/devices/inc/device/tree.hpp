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
    toggle_sequence const & blink_;
    dualshock2 const &      remote_control_;
    l293 const &            motor_left_;
    l293 const &            motor_right_;
    qtrhd06a const &        line_sensor_;
    timeout const &         offroute_timeout_;
    shell const &           shell_;

    void
    init(isr_event_emitter& events) const;
};

extern tree const g_device_tree;

} // namespace device
