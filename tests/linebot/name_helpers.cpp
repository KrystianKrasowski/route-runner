#include "linebot/domain/commands.hpp"
#include "name_helpers.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include <format>
#include <map>
#include <ostream>
#include <ranges>
#include <string>

namespace linebot
{

using command_names_map = std::map<command::value, std::string>;

class commands_parser
{
public:

    commands_parser(command remote_control, command_names_map names)
        : commands_{remote_control},
          names_map_{names}
    {
    }

    std::string
    to_string()
    {
        using namespace std::views;

        auto parsed_commands =
            iota(0, 16) | filter([&](int index) { return is_requested(index); })
            | transform([&](int index) { return to_command(index); })
            | transform([&](auto command) { return to_command_name(command); })
            | join_with(':');

        return std::ranges::to<std::string>(parsed_commands);
    }

private:

    command         commands_;
    command_names_map names_map_;

    bool
    is_requested(int bit_index)
    {
        return commands_.to_uint16() & (1 << bit_index);
    }

    command::value
    to_command(int bit_index)
    {
        return static_cast<command::value>(1 << bit_index);
    }

    std::string
    to_command_name(command::value command)
    {
        return names_map_.at(command);
    }
};

std::ostream&
operator<<(std::ostream& os, command cmds)
{
    command_names_map names = {
        {command::FORWARD, "FORWARD"},
        {command::BACKWARD, "BACKWARD"},
        {command::LEFT, "LEFT"},
        {command::RIGHT, "RIGHT"},
        {command::BREAK, "BREAK"},
        {command::FOLLOW, "FOLLOW"},
        {command::STOP, "NONE"},
    };

    commands_parser parser{cmds, names};
    return os << parser.to_string();
}

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

} // namespace linebot
