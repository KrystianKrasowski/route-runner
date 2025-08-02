#pragma once

#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include "linebot/printer_port.hpp"
#include <etl/optional.h>

namespace linebot
{

struct printer_port_mock : public printer_port
{
    etl::optional<mode>       printed_mode_       = etl::nullopt;
    etl::optional<pid_params> printed_pid_params_ = etl::nullopt;

    void
    print(const mode mode) override
    {
        printed_mode_ = etl::optional{mode};
    }

    void
    print(const pid_params& pid) override
    {
        printed_pid_params_ = etl::optional{pid};
    }
};

} // namespace linebot
