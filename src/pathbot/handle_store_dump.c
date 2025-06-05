#include <pathbot/api.h>
#include <pathbot/port.h>
#include <pathbot/store.h>

void
pathbot_handle_store_dump(void)
{
    pathbot_store_t *p_store = pathbot_store_get();

    pathbot_port_dump_mode(p_store->mode);
}
