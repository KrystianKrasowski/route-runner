#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "FreeRTOS.h"
#include "task.h"
#include <cstdint>
#include <etl/string.h>

namespace app
{

using task_name = etl::string<6>;

struct task_info
{
    TaskHandle_t handle_;
    task_name    name_;
};

template <class T, uint16_t stack_depth>
class task_base
{
public:

    task_base(task_name name, UBaseType_t priority)
        : name_{name},
          priority_{priority}
    {
    }

    static void
    rtos_entry(void* p_params)
    {
        auto p_task = static_cast<T*>(p_params);
        p_task->run();
    }

    TaskHandle_t
    register_rtos_task()
    {
        auto*       p_task    = static_cast<T*>(this);
        const char* task_name = name_.c_str();

        handle_ = xTaskCreateStatic(
            &task_base::rtos_entry,
            task_name,
            stack_depth,
            p_task,
            priority_,
            stack_,
            &task_control_block_
        );

        return handle_;
    }

    TaskHandle_t
    get_handle() const
    {
        return handle_;
    }

    task_info
    describe() const
    {
        return {handle_, name_};
    }

private:

    StackType_t  stack_[stack_depth];
    StaticTask_t task_control_block_;
    task_name    name_;
    UBaseType_t  priority_;
    TaskHandle_t handle_;
};

} // namespace app

#endif
