#include <mq.h>
#include <stdio.h>
#include <string.h>
#include <sysclock.h>
#include <usart2.h>
#include <tim15.h>

int
main(void)
{
    sysclock_init();
    usart2_tx_init();
    printf("Waiting...\n");
    mq_init();

    tim15_init();

    mq_message_t message;
    memset(&message, 0, sizeof(message));

    tim15_start();

    while (1)
    {
        if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) == MQ_SUCCESS)
        {
            printf("Timeout!\n");
        }
    }
}