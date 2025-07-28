#include "adapter/printer_shell.hpp"
#include "device/shell.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>
#include <cstdio>
#include <etl/format_spec.h>
#include <etl/map.h>
#include <etl/string_stream.h>
#include <etl/to_string.h>
#include <etl/utility.h>

namespace adapter
{

printer_shell&
printer_shell::of(device::shell& shell)
{
    static printer_shell adapter{shell};
    return adapter;
}

void
printer_shell::print(linebot::mode mode)
{
    print_buffer_.clear();

    print_buffer_ += "Mode: ";
    etl::to_string(static_cast<uint8_t>(mode), print_buffer_, true);
    print_buffer_ += "\n\r";

    shell_.send(print_buffer_);
}

void
printer_shell::print(linebot::pid_params& pid)
{
    print_buffer_.clear();

    print_buffer_ += "PID: kp ";
    etl::to_string(pid.get_kp_as_int(), print_buffer_, true);
    print_buffer_ += ", ki ";
    etl::to_string(pid.get_ki_as_int(), print_buffer_, true);
    print_buffer_ += ", kd ";
    etl::to_string(pid.get_kd_as_int(), print_buffer_, true);
    print_buffer_ += "\n\r";

    shell_.send(print_buffer_);
}

} // namespace adapter
