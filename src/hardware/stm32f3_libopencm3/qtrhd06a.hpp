#pragma once

#include "device/qtrhd06a.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

class qtrhd06a : public device::qtrhd06a
{
public:

    static qtrhd06a&
    of(volatile uint16_t* const p_buffer, uint8_t buffer_length);

    etl::array<uint8_t, device::qtrhd06a::VALUES_LENGTH>
    read() override;

private:

    volatile uint16_t* const p_buffer_;
    uint8_t const            buffer_length_;

    qtrhd06a(volatile uint16_t* const p_buffer, uint8_t buffer_length)
        : p_buffer_{p_buffer},
          buffer_length_{buffer_length}
    {
    }
};

} // namespace hardware
