#pragma once

#include <cstddef>
#include <etl/string.h>

namespace device
{

struct shell
{
    static constexpr size_t MAX_LENGTH = 32;

    virtual char
    read() const = 0;

    virtual void
    send(char* data, uint8_t length) const = 0;
};

} // namespace device
