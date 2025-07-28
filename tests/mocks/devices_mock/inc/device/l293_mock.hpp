#pragma once

#include "device/l293.hpp"
#include <cstdint>
#include <optional>

namespace device
{

struct l293_mock : public l293
{
    std::optional<rotation> applied_rotation_   = std::nullopt;
    std::optional<uint8_t>  applied_duty_cycle_ = std::nullopt;

    void
    rotate(rotation direction) override
    {
        applied_rotation_ = std::optional(direction);
    }

    void
    enable(uint8_t duty_cycle) override
    {
        applied_duty_cycle_ = std::optional(duty_cycle);
    }

    void
    disable() override
    {
    }
};

} // namespace device
