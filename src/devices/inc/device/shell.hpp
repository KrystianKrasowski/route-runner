#pragma once

#include <cstddef>
#include <etl/string.h>

namespace device
{

struct shell
{
    static constexpr size_t MAX_LENGTH = 100;

    virtual char
    read() = 0;

    virtual void
    send(char* data, uint8_t length) = 0;
};

} // namespace device
