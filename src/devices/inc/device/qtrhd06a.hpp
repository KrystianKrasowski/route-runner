#pragma once

#include <cstdint>
#include <etl/array.h>

namespace device
{

struct qtrhd06a
{
    static constexpr uint8_t VALUES_LENGTH = 6;

    virtual etl::array<uint8_t, VALUES_LENGTH>
    read() = 0;
};

} // namespace device
