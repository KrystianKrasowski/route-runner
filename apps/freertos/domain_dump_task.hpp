#ifndef _APPLICATION_TASK_DOMAIN_DUMP_H
#define _APPLICATION_TASK_DOMAIN_DUMP_H

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class domain_dump_task : public task_base<domain_dump_task, 96>
{
public:

    static domain_dump_task&
    of(const shell_stream& shell_stream,
       linebot::api&       api,
       EventGroupHandle_t  event_group);

    void
    run();

private:

    const shell_stream& shell_stream_;
    linebot::api&       api_;
    EventGroupHandle_t  event_group_;

    domain_dump_task(
        const shell_stream& shell_stream,
        linebot::api&       api,
        EventGroupHandle_t  event_group
    )
        : task_base{"domain dump", 1},
          shell_stream_{shell_stream},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app

#endif
