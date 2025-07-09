#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "FreeRTOS.h"
#include "task.h"
#include <cstdint>
#include <etl/string.h>

namespace app
{

template <typename T, uint16_t stack_depth>
class task_base
{
public:

    task_base(etl::string<16> name, UBaseType_t priority)
        : name{name}, priority{priority}
    {
    }

    TaskHandle_t
    register_rtos_task()
    {
        auto       *p_task    = static_cast<T *>(this);
        const char *task_name = name.c_str();

        handle = xTaskCreateStatic(
            &task_base::rtos_entry,
            task_name,
            stack_depth,
            p_task,
            priority,
            stack,
            &task_control_block
        );

        return handle;
    }

    static void
    rtos_entry(void *p_params)
    {
        auto p_task = static_cast<T *>(p_params);
        p_task->run();
    }

private:

    etl::string<16> name;
    UBaseType_t     priority;
    StackType_t     stack[stack_depth];
    StaticTask_t    task_control_block;
    TaskHandle_t    handle;
};

} // namespace app

#endif
