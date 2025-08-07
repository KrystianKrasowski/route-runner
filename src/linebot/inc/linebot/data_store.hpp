#pragma once

#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include "linebot/domain/remote_control.hpp"
#include <cstdint>
#include <etl/circular_buffer.h>

namespace linebot
{

struct data_store
{
    static constexpr uint8_t ERROR_HISTORY_LENGTH{10};

    etl::circular_buffer<int8_t, ERROR_HISTORY_LENGTH> errors_;

    remote_control remote_control_{remote_control::STOP};
    mode           mode_{mode::MANUAL};
    pid_params     pid_params_{640, 2, 4200};
    coordinates    line_position_;

    static data_store&
    of();

private:

    data_store()
        : line_position_{coordinates::of_6(0, 0, 0, 0, 0, 0)}
    {
    }
};

} // namespace linebot
