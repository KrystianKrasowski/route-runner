#include "name_helpers.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/motion_control.hpp"
#include <format>
#include <map>
#include <ostream>
#include <ranges>
#include <string>

namespace linebot
{

using command_names_map = std::map<motion_control::command, std::string>;

class commands_parser
{
public:

    commands_parser(motion_control remote_control, command_names_map names)
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

    motion_control    commands_;
    command_names_map names_map_;

    bool
    is_requested(int bit_index)
    {
        return commands_.to_uint16() & (1 << bit_index);
    }

    motion_control::command
    to_command(int bit_index)
    {
        return static_cast<motion_control::command>(1 << bit_index);
    }

    std::string
    to_command_name(motion_control::command command)
    {
        return names_map_.at(command);
    }
};

std::ostream&
operator<<(std::ostream& os, motion_control cmds)
{
    command_names_map names = {
        {motion_control::FORWARD, "FORWARD"},
        {motion_control::BACKWARD, "BACKWARD"},
        {motion_control::LEFT, "LEFT"},
        {motion_control::RIGHT, "RIGHT"},
        {motion_control::BREAK, "BREAK"},
        {motion_control::FOLLOW, "FOLLOW"},
        {motion_control::STOP, "NONE"},
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
