#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class domain_dump_task
    : public task_base<domain_dump_task, TASK_MEM_DOMAIN_DUMP>
{
public:

    static domain_dump_task&
    of(const shell_stream& shell_stream,
       const event_group&  event_group,
       linebot::api&       api);

    void
    run();

    domain_dump_task(const domain_dump_task& other) = delete;

    domain_dump_task(domain_dump_task&& other) = delete;

    domain_dump_task&
    operator=(const domain_dump_task& other) = delete;

    domain_dump_task&
    operator=(domain_dump_task&& other) = delete;

private:

    const shell_stream& shell_stream_;
    const event_group&  event_group_;
    linebot::api&       api_;

    domain_dump_task(
        const shell_stream& shell_stream,
        const event_group&  event_group,
        linebot::api&       api
    )
        : task_base{"dmdmp", 1},
          shell_stream_{shell_stream},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
