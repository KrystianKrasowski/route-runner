#include "device/isr_event_emitter.hpp"
#include "device/tree.hpp"

class dummy_event_emitter : public device::isr_event_emitter
{
public:

    void
    emit(device::event_id id) override
    {
        (void)id;
    }
};

static dummy_event_emitter events;

int
main()
{
    auto tree = device::tree::of(events);
    tree.toggle_sequence_.change_sequence(0xd);

    while (true)
    {
    }
}
