#pragma once

#include "linebot/data_store.hpp"
#include "linebot/domain/pid_params.hpp"
#include <cstdint>

namespace linebot
{

class pid_regulator
{
    using errors_buffer =
        etl::circular_buffer<int8_t, data_store::ERROR_HISTORY_LENGTH>;

public:

    pid_regulator(pid_params& config, errors_buffer& past_errors)
        : config_{config},
          past_errors_{past_errors}
    {
    }

    int8_t
    regulate(int8_t error)
    {
        int16_t errors_sum     = sum_past_errors();
        int8_t  previous_error = get_last_error();

        int16_t p = config_.kp * error;
        int16_t i = config_.ki * errors_sum;
        int16_t d = config_.kd * static_cast<int16_t>(error - previous_error);

        int16_t steering_value = p + i + d;

        if (steering_value > 100)
        {
            steering_value = 100;
        }

        if (steering_value < -100)
        {
            steering_value = -100;
        }

        past_errors_.push(error);

        return static_cast<int8_t>(steering_value);
    }

    int8_t
    get_last_error()
    {
        return past_errors_.empty() ? 0 : past_errors_.back();
    }

private:

    const pid_params& config_;
    errors_buffer&    past_errors_;

    int16_t
    sum_past_errors()
    {
        int16_t sum = 0;

        for (auto error : past_errors_)
        {
            sum += error;
        }

        return sum;
    }
};

} // namespace linebot
