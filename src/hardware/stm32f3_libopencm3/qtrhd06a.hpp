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

    explicit qtrhd06a(data_store& store);

    etl::array<uint8_t, device::qtrhd06a::VALUES_LENGTH>
    read() const override;

private:

    data_store& store_;
};

} // namespace hardware
