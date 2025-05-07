#include <adapters/route_guard.h>
#include <devices/timeout_guard.h>

int
adapter_route_guard_read(void)
{
    return device_timeout_guard_read(DEVICE_TIEMOUT_GUARD_ROUTE);
}
