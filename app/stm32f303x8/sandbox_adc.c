#include <mq.h>
#include <qtrhd06a.h>
#include <stdio.h>
#include <string.h>
#include <sysclock.h>
#include <usart2.h>

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
        if (mq_pull(MQ_TOPIC_COORDS, &message) == MQ_SUCCESS)
        {
            uint8_t *pos = message.payload.coords;
            printf("V1: %d; V2: %d; V3: %d; V4: %d; V5: %d; V6: %d\n",
                   pos[0],
                   pos[1],
                   pos[2],
                   pos[3],
                   pos[4],
                   pos[5]);
        }
    }
}