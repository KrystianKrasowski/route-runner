#pragma once

#include "linebot/domain/commands.hpp"
#include "linebot/domain/maneuver.hpp"
#include <ostream>

namespace linebot
{

std::ostream&
operator<<(std::ostream& os, commands cmds);

std::ostream&
operator<<(std::ostream& os, maneuver man);

} // namespace linebot
