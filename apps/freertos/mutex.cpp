#include "mutex.hpp"

namespace app
{

mutex&
mutex::of()
{
    // This should definitely use some object pool, but for now there is only
    // need for one mutex in whole application. However, keep that in mind.
    static mutex m;
    m.handle_ = xSemaphoreCreateMutexStatic(&m.buffer_);
    return m;
}

BaseType_t
mutex::take()
{
    return xSemaphoreTake(handle_, portMAX_DELAY);
}

BaseType_t
mutex::take(uint16_t timeout)
{
    return xSemaphoreTake(handle_, pdMS_TO_TICKS(timeout));
}

BaseType_t
mutex::give()
{
    return xSemaphoreGive(handle_);
}

} // namespace app
