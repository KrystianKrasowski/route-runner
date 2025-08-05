#include "name_helpers.hpp"
#include "linebot/domain/actions.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include <format>
#include <map>
#include <ostream>
#include <string>

namespace linebot
{

std::ostream&
operator<<(std::ostream& os, maneuver m)
{
    std::map<maneuver::direction, std::string> names = {
        {maneuver::FORWARD, "FORWARD"},
        {maneuver::BACKWARD, "BACKWARD"},
        {maneuver::NONE, "NONE"},
    };

    return os << std::format(
               "Motion[{}, {}]", names.at(m.get_direction()), m.get_correction()
           );
}

std::ostream&
operator<<(std::ostream& os, mode::value m)
{
    std::map<mode::value, std::string> names = {
        {mode::MANUAL, "MANUAL"},
        {mode::LINE_DETECTED, "LINE_DETECTED"},
        {mode::FOLLOWING, "FOLLOWING"},
        {mode::RECOVERING, "RECOVERING"}
    };

    return os << "mode::" << names.at(m);
}

std::ostream&
operator<<(std::ostream& os, const remote_control commands)
{
    return os << commands.as_uint();
}

std::ostream&
operator<<(std::ostream& os, const actions a)
{
    return os << a.as_uint();
}

} // namespace linebot
