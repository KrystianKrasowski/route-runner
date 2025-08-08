#pragma once

#include "data_store.hpp"
#include "device/qtrhd06a.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

class qtrhd06a : public device::qtrhd06a
{
public:

    static qtrhd06a&
    of(data_store& store);

    etl::array<uint8_t, device::qtrhd06a::VALUES_LENGTH>
    read() override;

private:

    data_store& store_;

    qtrhd06a(data_store& store)
        : store_{store}
    {
    }
};

} // namespace hardware
