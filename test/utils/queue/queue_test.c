#include "queue.h"
#include "unity.h"
#include <stdio.h>

#define TOPIC QUEUE_TOPIC_REMOTE_CONTROLLER_COMMAND

void
setUp(void)
{
}

void
tearDown(void)
{
    queue_clear(TOPIC);
}

void
should_enqueue(void)
{
    // when
    queue_message_t message_in1 = queue_message_create_command(11);
    queue_status_t  result      = queue_push(TOPIC, message_in1);

    // then
    TEST_ASSERT_EQUAL(QUEUE_STATUS_SUCCESS, result);
}

void
should_dequeue_in_FIFO_order(void)
{
    // given
    queue_push(TOPIC, queue_message_create_command(11));
    queue_push(TOPIC, queue_message_create_command(22));
    queue_push(TOPIC, queue_message_create_command(33));

    // when
    queue_message_t message1 = {};
    queue_message_t message2 = {};
    queue_message_t message3 = {};

    queue_pull(TOPIC, &message1);
    queue_pull(TOPIC, &message2);
    queue_pull(TOPIC, &message3);

    // then
    TEST_ASSERT_EQUAL(11, message1.payload.command);
    TEST_ASSERT_EQUAL(22, message2.payload.command);
    TEST_ASSERT_EQUAL(33, message3.payload.command);
}

void
should_not_enqueue_in_full_queue(void)
{
    // given
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        queue_push(TOPIC, queue_message_create_command(i + 10));
    }

    // when
    queue_status_t result = queue_push(TOPIC, queue_message_create_command(20));

    // then
    TEST_ASSERT_EQUAL(QUEUE_STATUS_MESSAGES_FULL, result);
}

void
should_dequeue_null_from_empty_queue(void)
{
    // when
    queue_message_t *message = NULL;
    queue_status_t   result  = queue_pull(TOPIC, message);

    // then
    TEST_ASSERT_NULL(message);
    TEST_ASSERT_EQUAL(QUEUE_STATUS_MESSAGES_EMPTY, result);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_enqueue);
    RUN_TEST(should_dequeue_in_FIFO_order);
    RUN_TEST(should_not_enqueue_in_full_queue);
    RUN_TEST(should_dequeue_null_from_empty_queue);
    return UNITY_END();
}