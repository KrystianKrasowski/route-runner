#include "queue.h"
#include "remote-control.h"
#include "tim3.h"
#include <stdint.h>

#define SEQUENCE_SIZE 15

static const remote_control_command_t sequence[SEQUENCE_SIZE] = {
    REMOTE_CONTROL_STOP,
    REMOTE_CONTROL_STOP,
    REMOTE_CONTROL_STOP,
    REMOTE_CONTROL_STOP,
    REMOTE_CONTROL_STOP,
    REMOTE_CONTROL_FORWARD,
    REMOTE_CONTROL_FORWARD_RIGHT,
    REMOTE_CONTROL_FORWARD_LEFT,
    REMOTE_CONTROL_FORWARD_LEFT,
    REMOTE_CONTROL_FORWARD_LEFT,
    REMOTE_CONTROL_BACKWARD,
    REMOTE_CONTROL_BACKWARD_RIGHT,
    REMOTE_CONTROL_BACKWARD_LEFT,
    REMOTE_CONTROL_BACKWARD_LEFT,
    REMOTE_CONTROL_BACKWARD_LEFT,
};

static volatile remote_control_command_t last_command = -1;
static volatile uint8_t                  index        = 0;

void
remote_control_init(void)
{
    tim3_ch1_init();
}

void
tim3_ch1_compare_isr(void)
{
    remote_control_command_t command = sequence[index++];

    if (last_command != command)
    {
        last_command = command;
        queue_message_t message = queue_message_create_command(command);
        queue_push(QUEUE_TOPIC_REMOTE_CONTROL_COMMAND, message);
    }

    if (index >= SEQUENCE_SIZE)
    {
        index = 0;
    }
}