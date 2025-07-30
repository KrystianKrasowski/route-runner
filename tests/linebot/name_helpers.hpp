#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include <ostream>

namespace linebot
{

std::ostream&
operator<<(std::ostream& os, command c);

std::ostream&
operator<<(std::ostream& os, maneuver m);

std::ostream&
operator<<(std::ostream& os, mode::value m);

} // namespace linebot
