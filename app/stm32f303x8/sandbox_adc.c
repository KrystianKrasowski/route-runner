#include <qtrhd06a.h>
#include <mq.h>
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
    mq_init();

    qtrhd06a_init();

    mq_message_t message;
    memset(&message, 0, sizeof(message));

    while (1)
    {
        if (mq_pull(MQ_TOPIC_LINE_POSITION, &message) == MQ_SUCCESS)
        {
            uint8_t *pos = message.payload.line_position;
            printf("V1: %d; V2: %d; V3: %d; V4: %d; V5: %d; V6: %d\n", pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
        }
    }
}