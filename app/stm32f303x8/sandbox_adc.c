#include <qtrhd06a.h>
#include <queue.h>
#include <stdio.h>
#include <sysclock.h>
#include <usart2.h>
#include <string.h>

int
main(void)
{
    sysclock_init();
    usart2_tx_init();
    printf("Waiting for readings...\n");

    qtrhd06a_init();

    queue_message_t message;
    memset(&message, 0, sizeof(message));

    while (1)
    {
        if (queue_pull(QUEUE_TOPIC_LINE_POSITION, &message) == QUEUE_SUCCESS)
        {
            uint16_t *pos = message.payload.line_position;
            printf("V1: %d; V2: %d; V3: %d\n", pos[0], pos[1], pos[2]);
        }
    }
}