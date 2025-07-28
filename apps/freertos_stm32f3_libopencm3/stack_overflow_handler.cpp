#include "stack_overflow_handler.hpp"
#include "FreeRTOS.h"
#include "device/toggle_sequence.hpp"
#include "task.h"

namespace app
{

static stack_overflow_handler* p_handler = nullptr;

stack_overflow_handler&
stack_overflow_handler::hook(device::toggle_sequence& blink)
{
    static stack_overflow_handler handler{blink};
    p_handler = &handler;
    return handler;
}

void
stack_overflow_handler::handle()
{
    blink_.change_sequence(0xd);
}

} // namespace app

extern "C"
{
    void
    vApplicationStackOverflowHook(TaskHandle_t h_task, char* task_name)
    {
        if (app::p_handler)
        {
            app::p_handler->handle();
        }

        while (1)
        {
        }

        (void)h_task;
        (void)task_name;
    }
}
