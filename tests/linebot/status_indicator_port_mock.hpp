#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/status_indicator_port.hpp"
#include <optional>

namespace linebot
{

struct status_indicator_port_mock : public status_indicator_port
{
    std::optional<mode> applied_mode_ = std::nullopt;

    void
    apply(mode mode) override
    {
        applied_mode_ = std::optional(mode);
    }
};

} // namespace linebot
