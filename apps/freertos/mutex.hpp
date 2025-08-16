#pragma once

#include "FreeRTOS.h"
#include "semphr.h"

namespace app
{

class mutex
{
public:

    static mutex&
    of();

    BaseType_t
    take();

    BaseType_t
    take(uint16_t timeout);

    BaseType_t
    give();

private:

    StaticSemaphore_t buffer_;
    SemaphoreHandle_t handle_;

    mutex() = default;
};

} // namespace app
