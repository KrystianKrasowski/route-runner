#pragma once

namespace device
{

enum class event_id
{
    DUALSHOCK2_RX_COMPLETE = 1,
    QTRHD06A_CONVERSION_COMPLETE,
    TIMEOUT,
    SHELL_COMMANDED,
};

class isr_event_emitter
{
public:

    virtual void
    emit(event_id id) = 0;
};

} // namespace device
