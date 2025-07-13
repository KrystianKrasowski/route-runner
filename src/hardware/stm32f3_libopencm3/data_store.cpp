#include "data_store.hpp"
#include <cstdint>

namespace hardware
{

void
data_store::on_dualshock2_rx_isr()
{
    for (uint8_t i = 0; i < dualshock2_buffer_length; i++)
    {
        p_dualshock2_rbuff[i] = p_dualshock2_wbuff[i];
    }
}

} // namespace hardware
