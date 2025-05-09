#include "mode.h"

bool
mode_is_tracking(pathbot_mode_t mode)
{
    return PATHBOT_MODE_FOLLOWING == mode || PATHBOT_MODE_RECOVERING == mode;
}

bool
mode_is_detected(pathbot_mode_t mode)
{
    return PATHBOT_MODE_DETECTED == mode;
}

bool
mode_is_manual(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_MANUAL == mode;
}

bool
mode_is_following(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_FOLLOWING == mode;
}

bool
mode_is_recovering(pathbot_mode_t const mode)
{
    return PATHBOT_MODE_RECOVERING == mode;
}
