#pragma once

#include <cstdint>

namespace device
{

enum dualshock2_command
{
    NONE     = 0,
    SELECT   = 1,
    L3       = 2,
    R3       = 4,
    START    = 8,
    UP       = 16,
    RIGHT    = 32,
    DOWN     = 64,
    LEFT     = 128,
    L2       = 256,
    R2       = 512,
    L1       = 1024,
    R1       = 2048,
    TRIANGLE = 4096,
    CIRCLE   = 8192,
    CROSS    = 16384,
    SQUARE   = 32768,
};

class dualshock2
{
public:

    virtual uint16_t
    read() = 0;
};

} // namespace device
