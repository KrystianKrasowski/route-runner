#include "motion.h"
#include "queue.h"
#include "usart2.h"
#include <stdio.h>
#include <string.h>

void
motion_init(void)
{
    usart2_tx_init();
}

void
motion_apply_task(void)
{
    queue_message_t message;
    memset(&message, 0, sizeof(message));

    if (queue_pull(QUEUE_TOPIC_REMOTE_CONTROL_COMMAND, &message) ==
        QUEUE_STATUS_SUCCESS)
    {
        printf("Command: %d\n", message.payload.command);
    }
}