#include "data_store.hpp"
#include <cstdint>

namespace hardware
{

void
data_store::on_dualshock2_rx_isr()
{
    for (uint8_t i = 0; i < DUALSHOCK2_BUFFER_LENGTH; i++)
    {
        p_dualshock2_rbuff[i] = p_dualshock2_wbuff[i];
    }
}

void
data_store::on_qtrhd06a_conversion_isr()
{
    for (uint8_t i = 0; i < QTRHD06A_BUFFER_LENGTH; i++)
    {
        p_qtrhd06a_rbuff[i] = p_qtrhd06a_wbuff[i];
    }
}

} // namespace hardware
