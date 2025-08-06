#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/status_indicator_port.hpp"
#include <optional>

namespace linebot
{

struct status_indicator_port_mock : public status_indicator_port
{
    std::optional<mode> applied_mode_ = std::nullopt;
    int                 apply_count_  = 0;

    void
    apply(mode mode) override
    {
        applied_mode_ = std::optional(mode);
        apply_count_++;
    }

    void
    reset()
    {
        apply_count_ = 0;
    }
};

} // namespace linebot
