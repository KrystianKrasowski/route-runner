#include "adapter/route_guard_timeout.hpp"

namespace adapter
{

route_guard_timeout&
route_guard_timeout::of()
{
    static route_guard_timeout adapter;
    return adapter;
}

void
route_guard_timeout::start()
{
}

void
route_guard_timeout::stop()
{
}

} // namespace adapter
