#ifndef _DEVICE_TOGGLE_SEQUENCE_H
#define _DEVICE_TOGGLE_SEQUENCE_H

#include <cstdint>

namespace device
{

class toggle_sequence
{
public:

    virtual void
    change_sequence(uint8_t value) = 0;
};

} // namespace device

#endif
