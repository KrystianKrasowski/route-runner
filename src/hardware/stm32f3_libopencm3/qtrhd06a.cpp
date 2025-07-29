#include "qtrhd06a.hpp"
#include "device/qtrhd06a.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

qtrhd06a&
qtrhd06a::of(volatile uint16_t* const p_buffer, uint8_t buffer_length)
{
    static qtrhd06a device{p_buffer, buffer_length};
    return device;
}

etl::array<uint8_t, device::qtrhd06a::VALUES_LENGTH>
qtrhd06a::read()
{
    uint16_t l3 = 0, l2 = 0, l1 = 0, r1 = 0, r2 = 0, r3 = 0;

    for (uint8_t i = 0; i < buffer_length_; i += 4)
    {
        r1 += (p_buffer_[i] >> 8) & 0xff;
        r3 += (p_buffer_[i]) & 0xff;
        l1 += (p_buffer_[i + 1] >> 8) & 0xff;
        r2 += (p_buffer_[i + 1]) & 0xff;
        l2 += (p_buffer_[i + 2] >> 8) & 0xff;
        l3 += (p_buffer_[i + 3] >> 8) & 0xff;
    }

    etl::array result{
        static_cast<uint8_t>(l3 / 10),
        static_cast<uint8_t>(l2 / 10),
        static_cast<uint8_t>(l1 / 10),
        static_cast<uint8_t>(r1 / 10),
        static_cast<uint8_t>(r2 / 10),
        static_cast<uint8_t>(r3 / 10)
    };

    return result;
}

} // namespace hardware
