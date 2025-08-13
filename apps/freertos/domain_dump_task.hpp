#ifndef _APPLICATION_TASK_DOMAIN_DUMP_H
#define _APPLICATION_TASK_DOMAIN_DUMP_H

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class domain_dump_task : public task_base<domain_dump_task, 128>
{
public:

    static domain_dump_task&
    of(linebot::api&      api,
       EventGroupHandle_t event_group,
       shell_stream&      shell_stream);

    void
    run();

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;
    shell_stream&      shell_stream_;

    domain_dump_task(
        linebot::api&      api,
        EventGroupHandle_t event_group,
        shell_stream&      shell_stream
    )
        : task_base{"domain dump", 1},
          api_{api},
          event_group_{event_group},
          shell_stream_{shell_stream}
    {
    }
};

} // namespace app

#endif
