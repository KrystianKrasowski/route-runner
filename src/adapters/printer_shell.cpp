#include "adapter/printer_shell.hpp"
#include "device/shell.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>
#include <etl/map.h>
#include <etl/string_stream.h>
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

    etl::string_stream stream{print_buffer_};

    stream << "MODE: " << static_cast<uint8_t>(mode) << "\n\r";

    shell_.send(print_buffer_);
}

void
printer_shell::print(linebot::pid_params& pid)
{
    print_buffer_.clear();

    etl::string_stream stream{print_buffer_};
    stream << "PID: kp " << pid.kp * 100 << ", ki " << pid.ki * 100 << ", kd "
           << pid.kd * 100 << "\n\r";

    shell_.send(print_buffer_);
}

} // namespace adapter
