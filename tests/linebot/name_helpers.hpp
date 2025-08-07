#pragma once

#include "linebot/domain/actions.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/remote_control.hpp"
#include <ostream>

namespace linebot
{

std::ostream&
operator<<(std::ostream& os, maneuver m);

std::ostream&
operator<<(std::ostream& os, mode::value m);

std::ostream&
operator<<(std::ostream& os, const remote_control commands);

std::ostream&
operator<<(std::ostream& os, const actions a);

} // namespace linebot
