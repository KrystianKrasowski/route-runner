#include "dualshock2.h"
#include <queue.h>
#include <stdint.h>
#include <tim3.h>

#define SEQUENCE_SIZE 15

static const uint16_t sequence[SEQUENCE_SIZE] = {
    DS2_NONE,
    DS2_NONE,
    DS2_NONE,
    DS2_NONE,
    DS2_NONE,
    DS2_R2,
    DS2_R2 | DS2_RIGHT,
    DS2_R2 | DS2_LEFT,
    DS2_R2 | DS2_LEFT,
    DS2_R2 | DS2_LEFT,
    DS2_L2,
    DS2_L2 | DS2_RIGHT,
    DS2_L2 | DS2_LEFT,
    DS2_L2 | DS2_LEFT,
    DS2_L2 | DS2_LEFT,
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
    // TODO: DS2 command should be enqueued only if it has changed
    queue_push(QUEUE_TOPIC_REMOTE_CONTROL, message);

    if (index >= SEQUENCE_SIZE)
    {
        index = 0;
    }
}