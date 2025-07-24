#pragma once

#include "device/toggle_sequence.hpp"
#include <cstdint>
#include <optional>

namespace device
{

struct toggle_sequence_mock : public toggle_sequence
{
    std::optional<uint8_t> applied_value_ = std::nullopt;

    void
    change_sequence(uint8_t value) override
    {
        applied_value_ = std::optional(value);
    }
};

} // namespace device
