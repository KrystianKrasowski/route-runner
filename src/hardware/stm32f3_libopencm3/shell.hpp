#pragma once

#include "device/shell.hpp"
#include <etl/string.h>

namespace hardware
{

class shell : public device::shell
{
public:

    static shell&
    of();

    char
    read() override;

    void
    send(etl::string<MAX_LENGTH>& message) override;

private:

    shell()
    {
    }
};

} // namespace hardware
