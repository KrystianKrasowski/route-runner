#include "adapter/route_guard_timeout.hpp"

namespace adapter
{

route_guard_timeout&
route_guard_timeout::of(device::timeout& offroute_timeout)
{
    static route_guard_timeout adapter{offroute_timeout};
    return adapter;
}

void
route_guard_timeout::start()
{
    offroute_timeout_.start(500);
}

void
route_guard_timeout::stop()
{
    offroute_timeout_.stop();
}

} // namespace adapter
