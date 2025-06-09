#include "task.h"
#include <devices/devices.h>
#include <pathbot/store.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    devices_init();
    pathbot_store_init(NULL);

    while (1)
    {
        task_handle_manual_control();
        task_handle_route_tracking();
        task_handle_immediate_stop();
        task_handle_domain_dump();
    }
}
