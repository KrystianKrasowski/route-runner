#pragma once

#include "coordinates_error_center_of_mass.hpp"
#include "linebot/domain/commands.hpp"
#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/maneuver.hpp"
#include <cstdint>
#include <etl/optional.h>

namespace linebot
{

constexpr int8_t CORRECTION_MANUAL_LEFT  = -50;
constexpr int8_t CORRECTION_MANUAL_RIGHT = 50;

inline maneuver
create_maneuver(commands remote_control)
{
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

    return {direction, correction};
}

inline maneuver
create_maneuver(coordinates& line_position)
{
    if (line_position.is_on_finish())
    {
        return maneuver::none();
    }

    coordinates_error_center_of_mass strategy;
    etl::optional<int8_t> correction = line_position.compute_error(strategy);

    if (correction.has_value())
    {
        return maneuver::forward(correction.value());
    }
    else
    {
        return maneuver::none();
    }
}

} // namespace linebot
