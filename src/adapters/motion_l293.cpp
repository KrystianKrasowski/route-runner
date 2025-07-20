#include "adapter/motion_l293.hpp"
#include "device/l293.hpp"
#include "linebot/domain/maneuver.hpp"
#include <cstdint>
#include <etl/absolute.h>
#include <etl/map.h>
#include <etl/utility.h>

namespace adapter
{

constexpr int8_t  INVERT_TRESHOLD = 50;
constexpr uint8_t DUTY_CYCLE_MIN  = 0;
constexpr uint8_t DUTY_CYCLE_MAX  = 100;

constexpr uint8_t
duty_cycle(int8_t correction)
{
    return etl::absolute(-2 * etl::absolute(correction) + 100);
}

motion_l293&
motion_l293::of(device::l293& motor_left, device::l293& motor_right)
{
    static motion_l293 motion_adapter{motor_left, motor_right};
    return motion_adapter;
}

void
motion_l293::apply(linebot::maneuver maneuver)
{
    motor_left_.disable();
    motor_right_.disable();

    auto rotation_left    = compute_left_rotation(maneuver);
    auto rotation_right   = compute_right_rotation(maneuver);
    auto duty_cycle_left  = compute_left_duty_cycle(maneuver);
    auto duty_cycle_right = compute_right_duty_cycle(maneuver);

    motor_left_.rotate(rotation_left);
    motor_right_.rotate(rotation_right);
    motor_left_.enable(duty_cycle_left);
    motor_right_.enable(duty_cycle_right);
}

device::l293::rotation
motion_l293::compute_left_rotation(linebot::maneuver maneuver)
{
    if (maneuver.is_forward() && maneuver.is_correction_below(-INVERT_TRESHOLD))
    {
        return device::l293::LEFT;
    }

    if (maneuver.is_backward()
        && maneuver.is_correction_below(-INVERT_TRESHOLD))
    {
        return device::l293::RIGHT;
    }

    if (maneuver.is_correction_at(-INVERT_TRESHOLD))
    {
        return device::l293::NONE;
    }

    return to_rotation(maneuver.get_direction());
}

device::l293::rotation
motion_l293::compute_right_rotation(linebot::maneuver maneuver)
{
    if (maneuver.is_forward() && maneuver.is_correction_above(INVERT_TRESHOLD))
    {
        return device::l293::LEFT;
    }

    if (maneuver.is_backward() && maneuver.is_correction_above(INVERT_TRESHOLD))
    {
        return device::l293::RIGHT;
    }

    if (maneuver.is_correction_at(INVERT_TRESHOLD))
    {
        return device::l293::NONE;
    }

    return to_rotation(maneuver.get_direction());
}

uint8_t
motion_l293::compute_left_duty_cycle(linebot::maneuver maneuver)
{
    if (linebot::maneuver::NONE == maneuver.get_direction())
    {
        return DUTY_CYCLE_MIN;
    }

    if (maneuver.is_correction_below(0))
    {
        return duty_cycle(maneuver.get_correction());
    }

    return DUTY_CYCLE_MAX;
}

uint8_t
motion_l293::compute_right_duty_cycle(linebot::maneuver maneuver)
{
    if (linebot::maneuver::NONE == maneuver.get_direction())
    {
        return DUTY_CYCLE_MIN;
    }

    if (maneuver.is_correction_above(0))
    {
        return duty_cycle(maneuver.get_correction());
    }

    return DUTY_CYCLE_MAX;
}

device::l293::rotation
motion_l293::to_rotation(linebot::maneuver::direction direction)
{
    switch (direction)
    {
    case linebot::maneuver::FORWARD:
        return device::l293::RIGHT;

    case linebot::maneuver::BACKWARD:
        return device::l293::LEFT;

    case linebot::maneuver::NONE:
    default:
        return device::l293::NONE;
    }
}

} // namespace adapter
