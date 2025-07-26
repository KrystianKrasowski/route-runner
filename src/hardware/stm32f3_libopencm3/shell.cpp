#include "shell.hpp"
#include <etl/string.h>

namespace hardware
{

shell&
shell::of()
{
    static shell device;
    return device;
}

char
shell::read()
{
    return 'd';
}

void
shell::send(etl::string<MAX_LENGTH>& message)
{
}

} // namespace hardware
