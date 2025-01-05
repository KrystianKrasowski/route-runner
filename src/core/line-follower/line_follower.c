#include "line-follower.h"

static bool standby = false;

void
line_follower_run(void)
{
    standby = false;
}

bool
line_follower_is_standby(void)
{
    return standby;
}