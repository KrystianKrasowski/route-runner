#pragma once

#include "coordinates_error_center_of_mass.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include "pid_regulator.hpp"
#include <cstdint>
#include <etl/optional.h>

namespace linebot
{

constexpr int8_t CORRECTION_MANUAL_LEFT  = -50;
constexpr int8_t CORRECTION_MANUAL_RIGHT = 50;

inline maneuver
create_maneuver(command remote_control)
{
    int8_t correction = 0;

    if (remote_control.have_left())
    {
        correction = -50;
    }
    else if (remote_control.have_right())
    {
        correction = 50;
    }

    maneuver::direction direction;

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

    return {direction, correction};
}

inline maneuver
create_maneuver(const coordinates& line_position, pid_regulator& pid)
{
    if (line_position.is_on_finish())
    {
        return maneuver::none();
    }

    coordinates_error_center_of_mass strategy;

    int8_t error =
        line_position.compute_error(strategy).value_or(pid.get_last_error());

    int8_t correction = pid.regulate(error);

    return maneuver::forward(correction);
}

} // namespace linebot
