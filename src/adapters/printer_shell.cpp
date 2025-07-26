#include "adapter/printer_shell.hpp"
#include "device/shell.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"

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
}

void
printer_shell::print(linebot::pid_params& pid)
{
}

} // namespace adapter
