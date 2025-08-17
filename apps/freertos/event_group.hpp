#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"

namespace app
{

class event_group
{
public:

    static event_group&
    of();

    EventGroupHandle_t
    get_handle() const;

    EventBits_t
    set_bits(uint8_t bits) const;

    EventBits_t
    wait_bits(
        EventBits_t bits_to_wait,
        bool        clear_on_exit,
        bool        wait_for_all_bits,
        uint16_t    timeout_ms
    ) const;

private:

    EventGroupHandle_t handle_;
    StaticEventGroup_t buffer_;

    event_group() = default;
};

} // namespace app
