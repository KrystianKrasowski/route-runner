#pragma once

#include "linebot/domain/motion_control.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include <ostream>

namespace linebot
{

std::ostream&
operator<<(std::ostream& os, motion_control c);

std::ostream&
operator<<(std::ostream& os, maneuver m);

std::ostream&
operator<<(std::ostream& os, mode::value m);

} // namespace linebot
