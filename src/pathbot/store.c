#include <pathbot/store.h>

static pathbot_store_t store;

pathbot_store_t *
pathbot_store_get(void)
{
    return &store;
}
