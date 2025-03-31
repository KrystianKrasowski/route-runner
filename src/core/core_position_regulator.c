#include "core_position_regulator.h"

#define KP 0.6
#define KI 0
#define KD 3.2

int8_t
core_position_regulate_pid(core_position_t *position)
{
    int8_t  previous   = core_position_last_error(position);
    int8_t  error      = core_position_update_error(position);
    int16_t all_errors = core_position_sum_errors(position);

    int16_t correction = KP * error + KI * all_errors + KD * (error - previous);

    if (correction > 100)
    {
        return 100;
    }
    else if (correction < -100)
    {
        return -100;
    }
    else
    {
        return correction;
    }
}