#include "linebot/motion_api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include <cstdint>

namespace linebot
{

motion_api&
motion_api::of(data_store& store, motion_port& port)
{
    static motion_api api{store, port};
    return api;
}

void
motion_api::apply(commands remote_control)
{
    if (store_.remote_control_ == remote_control)
    {
        return;
    }

    maneuver::direction direction  = maneuver::NONE;
    int8_t              correction = 0;

    if (remote_control.have_left())
    {
        correction = -50;
    }
    else if (remote_control.have_right())
    {
        correction = 50;
    }

    if (remote_control.have_forward())
    {
        direction = maneuver::FORWARD;
    }
    else if (remote_control.have_backward())
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
    store_.remote_control_ = remote_control;
}

void
motion_api::apply(coordinates line_position)
{
}

} // namespace linebot
