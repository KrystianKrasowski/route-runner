#pragma once

#include "linebot/domain/maneuver.hpp"
#include "linebot/motion_port.hpp"
#include <optional>

namespace linebot
{

struct motion_port_mock : public motion_port
{
    std::optional<maneuver> applied_maneuver_ = std::nullopt;

    void
    apply(maneuver maneuver) override
    {
        applied_maneuver_ = std::optional{maneuver};
    }
};

} // namespace linebot
