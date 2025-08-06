#ifndef _APPLICATION_TASK_DOMAIN_DUMP_H
#define _APPLICATION_TASK_DOMAIN_DUMP_H

#include "linebot/api.hpp"
#include "task_base.hpp"
#include "event_groups.h"

namespace app
{

class domain_dump_task : public task_base<domain_dump_task, 128>
{
public:

    static domain_dump_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    domain_dump_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"domain dump", 1},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app

#endif
