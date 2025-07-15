#include "linebot/motion_api.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include <cstdint>

namespace linebot
{

motion_api&
motion_api::of(motion_port& port)
{
    static motion_api api{port};
    return api;
}

void
motion_api::apply(commands commands)
{
    maneuver::direction direction  = maneuver::NONE;
    int8_t              correction = 0;

    if (commands.have_left())
    {
        correction = -50;
    }
    else if (commands.have_right())
    {
        correction = 50;
    }

    if (commands.have_forward())
    {
        direction = maneuver::FORWARD;
    }
    else if (commands.have_backward())
    {
        direction = maneuver::BACKWARD;
    }
    else
    {
        direction  = maneuver::NONE;
        correction = 0;
    }

    maneuver new_maneuver{direction, correction};
    port_.apply(new_maneuver);
}

void
motion_api::apply(coordinates line_position)
{
}

} // namespace linebot
