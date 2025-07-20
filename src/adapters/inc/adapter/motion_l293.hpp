#pragma once

#include "device/l293.hpp"
#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include <cstdint>

namespace adapter
{

class motion_l293 : public linebot::motion_port
{
public:

    static motion_l293&
    of(device::l293& motor_left, device::l293& motor_right);

    void
    apply(linebot::maneuver maneuver) override;

private:

    device::l293& motor_left_;
    device::l293& motor_right_;

    motion_l293(device::l293& motor_left, device::l293& motor_right)
        : motor_left_{motor_left},
          motor_right_{motor_right}
    {
    }

    device::l293::rotation
    compute_left_rotation(linebot::maneuver maneuver);

    device::l293::rotation
    compute_right_rotation(linebot::maneuver maneuver);

    uint8_t
    compute_left_duty_cycle(linebot::maneuver maneuver);

    uint8_t
    compute_right_duty_cycle(linebot::maneuver maneuver);

    device::l293::rotation
    to_rotation(linebot::maneuver::direction direction);
};

} // namespace adapter
