#include "adapter/motion_adapter_l293.hpp"
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

static auto rotation_map =
    etl::make_map<linebot::maneuver::direction, device::l293::rotation>(
        etl::pair{linebot::maneuver::FORWARD, device::l293::RIGHT},
        etl::pair{linebot::maneuver::BACKWARD, device::l293::LEFT},
        etl::pair{linebot::maneuver::NONE, device::l293::NONE}
    );

motion_adapter_l293&
motion_adapter_l293::of(device::l293& motor_left, device::l293& motor_right)
{
    static motion_adapter_l293 adapter{motor_left, motor_right};
    return adapter;
}

void
motion_adapter_l293::apply(linebot::maneuver maneuver)
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

inline device::l293::rotation
motion_adapter_l293::compute_left_rotation(linebot::maneuver maneuver)
{
    if (maneuver.is_correction_below(-INVERT_TRESHOLD) && maneuver.is_forward())
    {
        return device::l293::LEFT;
    }

    if (maneuver.is_correction_below(-INVERT_TRESHOLD)
        && maneuver.is_backward())
    {
        return device::l293::RIGHT;
    }

    if (maneuver.is_correction_at(-INVERT_TRESHOLD))
    {
        return device::l293::NONE;
    }

    return rotation_map.at(maneuver.get_direction());
}

inline device::l293::rotation
motion_adapter_l293::compute_right_rotation(linebot::maneuver maneuver)
{
    if (maneuver.is_correction_above(INVERT_TRESHOLD) && maneuver.is_forward())
    {
        return device::l293::RIGHT;
    }

    if (maneuver.is_correction_above(INVERT_TRESHOLD) && maneuver.is_backward())
    {
        return device::l293::LEFT;
    }

    if (maneuver.is_correction_at(INVERT_TRESHOLD))
    {
        return device::l293::NONE;
    }

    return rotation_map.at(maneuver.get_direction());
}

inline uint8_t
motion_adapter_l293::compute_left_duty_cycle(linebot::maneuver maneuver)
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

inline uint8_t
motion_adapter_l293::compute_right_duty_cycle(linebot::maneuver maneuver)
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

} // namespace adapter
