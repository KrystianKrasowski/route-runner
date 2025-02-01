#include "core_type.h"
#include "queue.h"
#include "tim3.h"
#include <stdint.h>

#define SEQUENCE_SIZE 15

static const uint16_t sequence[SEQUENCE_SIZE] = {
    CORE_REMOTE_CONTROL_NONE,
    CORE_REMOTE_CONTROL_NONE,
    CORE_REMOTE_CONTROL_NONE,
    CORE_REMOTE_CONTROL_NONE,
    CORE_REMOTE_CONTROL_NONE,
    CORE_REMOTE_CONTROL_FORWARD,
    CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_RIGHT,
    CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT,
    CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT,
    CORE_REMOTE_CONTROL_FORWARD | CORE_REMOTE_CONTROL_LEFT,
    CORE_REMOTE_CONTROL_BACKWARD,
    CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_RIGHT,
    CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT,
    CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT,
    CORE_REMOTE_CONTROL_BACKWARD | CORE_REMOTE_CONTROL_LEFT,
};

static volatile uint8_t index = 0;

void
dualshock2_init(void)
{
    tim3_ch1_init();
}

void
tim3_ch1_compare_isr(void)
{
    uint16_t command = sequence[index++];

    queue_message_t message = queue_message_create_command(command);
    queue_push(QUEUE_TOPIC_REMOTE_CONTROL, message);

    if (index >= SEQUENCE_SIZE)
    {
        index = 0;
    }
}