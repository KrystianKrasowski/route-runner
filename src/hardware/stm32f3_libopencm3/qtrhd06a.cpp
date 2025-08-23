#include "qtrhd06a.hpp"
#include "device/qtrhd06a.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

qtrhd06a::qtrhd06a(data_store& store)
    : store_{store}
{
}

etl::array<uint8_t, device::qtrhd06a::VALUES_LENGTH>
qtrhd06a::read() const
{
    uint16_t l3 = 0, l2 = 0, l1 = 0, r1 = 0, r2 = 0, r3 = 0;

    for (uint8_t i = 0; i < store_.QTRHD06A_BUFFER_LENGTH; i += 4)
    {
        r1 += (store_.p_qtrhd06a_rbuff_[i] >> 8) & 0xff;
        r3 += (store_.p_qtrhd06a_rbuff_[i]) & 0xff;
        l1 += (store_.p_qtrhd06a_rbuff_[i + 1] >> 8) & 0xff;
        r2 += (store_.p_qtrhd06a_rbuff_[i + 1]) & 0xff;
        l2 += (store_.p_qtrhd06a_rbuff_[i + 2] >> 8) & 0xff;
        l3 += (store_.p_qtrhd06a_rbuff_[i + 3] >> 8) & 0xff;
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
