#include <core/ports.h>
#include <tim15.h>

void
core_port_route_guard_init(void)
{
    tim15_init();
}

void
core_port_route_guard_start(void)
{
    tim15_start();
}

void
core_port_route_guard_reset(void)
{
    tim15_reset();
}

void
core_port_route_guard_stop(void)
{
    tim15_stop();
}