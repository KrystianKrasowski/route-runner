#include "motion.h"
#include "remote-control.h"

int
main(void)
{
    remote_control_init();
    motion_init();

    while (1)
    {
        motion_apply_task();
    }
}