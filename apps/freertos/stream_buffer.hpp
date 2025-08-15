#pragma once

#include "FreeRTOS.h"
#include "stream_buffer.h"
#include <cstddef>
#include <cstdint>
#include <device/shell.hpp>
#include <etl/string.h>

namespace app
{

template <size_t BUFFLEN>
class stream_buffer
{
public:

    static stream_buffer&
    of()
    {
        static stream_buffer<BUFFLEN> sb{BUFFLEN};
        sb.handle_ = xStreamBufferCreateStatic(
            BUFFLEN, BUFFLEN, sb.storage_, &sb.buffer_
        );
        return sb;
    }

    static stream_buffer&
    of(std::size_t trigger_bytes)
    {
        static stream_buffer<BUFFLEN> sb{trigger_bytes};
        sb.handle_ = xStreamBufferCreateStatic(
            BUFFLEN, trigger_bytes, sb.storage_, &sb.buffer_
        );
        return sb;
    }

    StreamBufferHandle_t
    get_handle() const
    {
        return handle_;
    }

    template <size_t STRLEN>
    void
    send(const etl::string<STRLEN>& message) const
    {
        size_t      offset = 0;
        char        chunk[BUFFLEN];
        const char* raw_message = message.c_str();

        while (offset < STRLEN)
        {
            memcpy(chunk, raw_message + offset, BUFFLEN);
            offset +=
                xStreamBufferSend(handle_, chunk, BUFFLEN, pdMS_TO_TICKS(1000));
        }
    }

    size_t
    receive(void* buffer, size_t length)
    {
        return xStreamBufferReceive(
            handle_, buffer, length, pdMS_TO_TICKS(100)
        );
    }

private:

    std::size_t          trigger_bytes_;
    uint8_t              storage_[BUFFLEN + 1];
    StaticStreamBuffer_t buffer_;
    StreamBufferHandle_t handle_;

    stream_buffer(std::size_t trigger_bytes)
        : trigger_bytes_{trigger_bytes}
    {
    }
};

using shell_stream = stream_buffer<device::shell::MAX_LENGTH>;

} // namespace app
