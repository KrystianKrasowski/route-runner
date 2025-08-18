#pragma once

#include "linebot/domain/coordinates.hpp"
#include "linebot/domain/mode.hpp"
#include "linebot/domain/pid_params.hpp"
#include "linebot/domain/remote_control.hpp"
#include <cstdint>
#include <etl/circular_buffer.h>

namespace linebot
{

using errors_buffer = etl::circular_buffer<int8_t, 10>;

struct data_store
{
    pid_params     pid_params_{640, 2, 4200};
    remote_control remote_control_{remote_control::STOP};
    mode           mode_{mode::MANUAL};
    coordinates    line_position_;
    errors_buffer  errors_;

    static data_store&
    of();

private:

    data_store()
        : line_position_{coordinates::of_6(0, 0, 0, 0, 0, 0)}
    {
    }
};

} // namespace linebot
