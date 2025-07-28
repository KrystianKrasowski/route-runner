#include "adapter/printer_shell.hpp"
#include "device/shell.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>
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

    etl::string<1> mode_number;
    etl::to_string(static_cast<uint8_t>(mode), mode_number);

    print_buffer_ += "Mode: ";
    print_buffer_ += mode_number;
    print_buffer_ += "\n\r";

    shell_.send(print_buffer_);
}

void
printer_shell::print(linebot::pid_params& pid)
{
    print_buffer_.clear();

    etl::string<3> kp;
    etl::string<3> ki;
    etl::string<3> kd;

    etl::to_string(pid.kp * 100, kp);
    etl::to_string(pid.ki * 100, ki);
    etl::to_string(pid.kd * 100, kd);
    
    print_buffer_ += "PID: kp ";
    print_buffer_ += kp;
    print_buffer_ += ", ki ";
    print_buffer_ += ki;
    print_buffer_ += ", kd ";
    print_buffer_ += kd;
    print_buffer_ += "\n\r";

    shell_.send(print_buffer_);
}

} // namespace adapter
