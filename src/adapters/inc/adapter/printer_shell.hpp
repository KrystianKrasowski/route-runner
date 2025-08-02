#pragma once

#include "device/shell.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include "linebot/printer_port.hpp"
#include <etl/optional.h>
#include <etl/string.h>

namespace adapter
{

class printer_shell : public linebot::printer_port
{
public:

    static printer_shell&
    of(device::shell& shell);

    void
    print(const linebot::mode mode) override;

    void
    print(const linebot::pid_params& pid) override;

private:

    device::shell&                         shell_;
    etl::string<device::shell::MAX_LENGTH> print_buffer_;

    printer_shell(device::shell& shell)
        : shell_{shell}
    {
    }
};

} // namespace adapter
