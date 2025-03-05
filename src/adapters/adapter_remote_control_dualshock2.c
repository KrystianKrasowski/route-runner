#include <core.h>
#include <dualshock2.h>
#include <stdbool.h>

static inline bool
is_forward(uint16_t raw_command);

static inline bool
is_backward(uint16_t raw_command);

static inline bool
is_right(uint16_t raw_command);

static inline bool
is_left(uint16_t raw_command);

static inline bool
is_break(uint16_t raw_command);

static inline bool
is_follow(uint16_t raw_command);

void
core_port_remote_control_init(void)
{
    dualshock2_init();
}

uint16_t
core_port_remote_control_map(uint16_t raw_command)
{
    uint16_t command = CORE_REMOTE_CONTROL_NONE;

    if (is_forward(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_FORWARD;
    }

    if (is_backward(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_BACKWARD;
    }

    if (is_right(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_RIGHT;
    }

    if (is_left(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_LEFT;
    }

    if (is_break(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_BREAK;
    }
    
    if (is_follow(raw_command))
    {
        command |= CORE_REMOTE_CONTROL_FOLLOW;
    }

    return command;
}

static inline bool
is_forward(uint16_t raw_command)
{
    return (raw_command & DS2_R2) && !(raw_command & DS2_L2);
}

static inline bool
is_backward(uint16_t raw_command)
{
    return !(raw_command & DS2_R2) && (raw_command & DS2_L2);
}

static inline bool
is_right(uint16_t raw_command)
{
    return (raw_command & DS2_RIGHT) && !(raw_command & DS2_LEFT);
}

static inline bool
is_left(uint16_t raw_command)
{
    return !(raw_command & DS2_RIGHT) && (raw_command & DS2_LEFT);
}

static inline bool
is_break(uint16_t raw_command)
{
    return raw_command & DS2_CIRCLE;
}

static inline bool
is_follow(uint16_t raw_command)
{
    return raw_command & DS2_CROSS;
}