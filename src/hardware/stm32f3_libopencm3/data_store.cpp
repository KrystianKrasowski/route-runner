#include "data_store.hpp"
#include <cstdint>

namespace hardware
{

void
data_store::swap_dualshock2_buffers_isr()
{
    volatile uint8_t* temp = p_dualshock2_rbuff_;
    p_dualshock2_rbuff_    = p_dualshock2_wbuff_;
    p_dualshock2_wbuff_    = temp;
}

void
data_store::swap_qtrhd06a_buffers_isr()
{
    volatile uint16_t* temp = p_qtrhd06a_rbuff_;
    p_qtrhd06a_rbuff_       = p_qtrhd06a_wbuff_;
    p_qtrhd06a_wbuff_       = temp;
}

} // namespace hardware
