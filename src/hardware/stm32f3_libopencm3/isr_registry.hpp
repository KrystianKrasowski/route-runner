#pragma once

#include "isr_handler.hpp"
#include <cstdint>

namespace hardware
{

void
isr_register(uint8_t nvic_number, isr_handler& handler);

}
