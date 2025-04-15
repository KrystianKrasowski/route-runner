#include "position_regulator.h"

#define KP 0.6
#define KI 0
#define KD 3.2

int8_t
position_regulate_pid(position_t const h_position)
{
    int8_t  previous   = position_last_error(h_position);
    int8_t  error      = position_update_error(h_position);
    int16_t all_errors = position_sum_errors(h_position);

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