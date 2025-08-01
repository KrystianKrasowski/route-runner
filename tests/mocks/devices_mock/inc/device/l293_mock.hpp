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
    int                     count_rotate_       = 0;
    int                     count_enable_       = 0;

    void
    rotate(rotation direction) override
    {
        applied_rotation_ = std::optional(direction);
        count_rotate_++;
    }

    void
    enable(uint8_t duty_cycle) override
    {
        applied_duty_cycle_ = std::optional(duty_cycle);
        count_enable_++;
    }

    void
    disable() override
    {
    }
};

} // namespace device
