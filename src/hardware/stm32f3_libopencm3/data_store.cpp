#include "data_store.hpp"
#include <cstdint>

namespace hardware
{

void
data_store::on_dualshock2_rx_isr()
{
    for (uint8_t i = 0; i < DUALSHOCK2_BUFFER_LENGTH; i++)
    {
        p_dualshock2_rbuff_[i] = p_dualshock2_wbuff_[i];
    }
}

void
data_store::on_qtrhd06a_conversion_isr()
{
    for (uint8_t i = 0; i < QTRHD06A_BUFFER_LENGTH; i++)
    {
        p_qtrhd06a_rbuff_[i] = p_qtrhd06a_wbuff_[i];
    }
}

void
data_store::clear_shell_output()
{
    for (uint8_t i = 0; i < SHELL_TXBUFF_LENGTH; i++)
    {
        p_shell_output_[i] = 0;
    }
}

} // namespace hardware
