#include "queue.h"
#include "unity.h"
#include <stdio.h>

void
setUp(void)
{
}

void
tearDown(void)
{
    queue_clear();
}

void
should_enqueue(void)
{
    // when
    queue_message_t message_in1 = queue_message_create_command(11);
    bool            result      = queue_push(message_in1);

    // then
    TEST_ASSERT_TRUE(result);
}

void
should_dequeue_in_FIFO_order(void)
{
    // given
    queue_push(queue_message_create_command(11));
    queue_push(queue_message_create_command(22));
    queue_push(queue_message_create_command(33));

    // when
    volatile queue_message_t *message1 = queue_pull();
    volatile queue_message_t *message2 = queue_pull();
    volatile queue_message_t *message3 = queue_pull();

    // then
    TEST_ASSERT_EQUAL(11, message1->payload.command);
    TEST_ASSERT_EQUAL(22, message2->payload.command);
    TEST_ASSERT_EQUAL(33, message3->payload.command);
}

void
should_not_enqueue_in_full_queue(void)
{
    // given
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        queue_push(queue_message_create_command(i + 10));
    }

    // when
    bool result = queue_push(queue_message_create_command(20));

    // then
    TEST_ASSERT_FALSE(result);
}

void
should_dequeue_null_from_empty_queue(void)
{
    // when
    volatile queue_message_t *message = queue_pull();

    // then
    TEST_ASSERT_NULL(message);
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