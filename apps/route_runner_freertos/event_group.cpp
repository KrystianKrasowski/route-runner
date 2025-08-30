#include "event_group.hpp"
#include <etl/pool.h>

namespace app
{

static etl::pool<event_group, 2> pool;

event_group&
event_group::of()
{
    event_group* events = pool.allocate();
    new (events) event_group;

    events->handle_ = xEventGroupCreateStatic(&events->buffer_);

    return *events;
}

EventGroupHandle_t
event_group::get_handle() const
{
    return handle_;
}

EventBits_t
event_group::set_bits(const uint8_t bits) const
{
    return xEventGroupSetBits(handle_, bits);
}

EventBits_t
event_group::wait_bits(
    EventBits_t bits_to_wait,
    bool        clear_on_exit,
    bool        wait_for_all_bits,
    uint16_t    timeout_ms
) const
{
    auto clear = clear_on_exit ? pdTRUE : pdFALSE;
    auto wait  = wait_for_all_bits ? pdTRUE : pdFALSE;

    return xEventGroupWaitBits(
        handle_, bits_to_wait, clear, wait, pdMS_TO_TICKS(timeout_ms)
    );
}

} // namespace app
